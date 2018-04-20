#include "stdafx.h"
#include "Server.h"

Server::Server()
{
	m_IM = new InterestManagement();
}

Server::~Server()
{
	delete m_Communication;
	delete m_ReceiveThread;
	delete m_InputThread;
	delete m_IM;
}

void Server::RunServer()
{
	try
	{
		std::cout << "Server Starting..." << std::endl;

		m_ReceiveThread = new std::thread(&Server::StartReceiveThread, this);
		m_ReceiveThread->detach();
		
		m_InputThread = new std::thread(&Server::StartInputThread, this);
		m_InputThread->detach();

		double previousTime = GetCurrentTime();
		double lag = 0.0;

		while (true)
		{
			double currentTime = GetCurrentTime();
			double elapsedTime = currentTime - previousTime;
			previousTime = currentTime;
			lag += elapsedTime;

			while (lag >= MS_INTERVAL)
			{
				//std::cout << "Frame. " << lag << std::endl;

				HandleReceivedPacketData();
				
				m_IM->UpdateInterest();

				SendPositionalPacketData();

				lag -= MS_INTERVAL;
			}
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}

void Server::StartReceiveThread()
{
	boost::asio::io_service io_service;
	m_Communication = new Communication(io_service);
	io_service.run();
}

void Server::StartInputThread()
{
	std::string input;
	std::cin >> input;

	if (input == "Close")
	{
		Server::~Server();
	}
}
void Server::HandleReceivedPacketData()
{
	if (!m_Communication->IsConnectDataQueueEmpty())
	{
		UpdateConnectionData();
	}

	if (!m_Communication->IsPositionPacketQueueEmpty())
	{
		UpdateClientPositionData();
	}

	if (!m_Communication->IsDisconnectPacketQueueEmpty())
	{
		UpdateDisconnectData();
	}
}

void Server::UpdateConnectionData()
{
	std::vector<ConnectData> connectionData = m_Communication->GetAllConnectData();

	for (size_t i = 0; i < connectionData.size(); i++)
	{
		std::cout << "Connected Client" << std::endl;
		Client* client = new Client(connectionData[i].EndPoint, connectionData[i].Packet, m_IM->GetClientListSize());
		m_IM->AddClient(client);
		ConfirmAcknowledgmentPacketArrived(m_IM->GetClientListSize() - 1);
	}
}

void Server::UpdateDisconnectData()
{
	std::vector<ClientDisconnectPacket> disconnectPacket = m_Communication->GetAllClientDisconnectPackets();

	for (size_t i = 0; i < disconnectPacket.size(); i++)
	{
		ConfirmAcknowledgmentPacketArrived(disconnectPacket[i].ClientID);
		m_IM->GetClientList()[disconnectPacket[i].ClientID]->SetConnectionStatus(false);
	}
}

void Server::UpdateClientPositionData()
{
	std::vector<ClientPositionPacket> positionPackets = m_Communication->GetAllClientPositionPackets();
	
	for (size_t i = 0; i < positionPackets.size(); i++)
	{
		if (m_IM->GetClientList()[positionPackets[i].ClientID]->GetConnectionStatus())
		{
			m_IM->GetClientList()[positionPackets[i].ClientID]->SetPos(positionPackets[i].X, positionPackets[i].Y, positionPackets[i].Z);
			m_IM->GetClientList()[positionPackets[i].ClientID]->SetRotationY(positionPackets[i].Rotation);
		}
	}

}

void Server::ConfirmAcknowledgmentPacketArrived(int clientid)
{
	m_Communication->Send(m_IM->GetClientList()[clientid]->GetEndpoint(), ServerAcknowledgmentPacket{ clientid });
}

void Server::SendPositionalPacketData()
{
	try
	{
		for (size_t i = 0; i < m_IM->GetClientListSize(); i++)
		{
			if (m_IM->GetClientList()[i]->GetConnectionStatus())
			{
				//Create Packets
				ServerPlayerPacket packet;

				packet.ClientID = *m_IM->GetClientList()[i]->GetID();
				packet.X = m_IM->GetClientList()[i]->GetPos()->X;
				packet.Y = m_IM->GetClientList()[i]->GetPos()->Y;
				packet.Z = m_IM->GetClientList()[i]->GetPos()->Z;
				packet.Rotation = *m_IM->GetClientList()[i]->GetRotationY();
				memcpy(packet.Username, m_IM->GetClientList()[i]->GetUsername(), USERNAME_SIZE);

				int seenSize = m_IM->GetClientList()[i]->GetSeenClients().size();
				//Send
				for (size_t j = 0; j < seenSize; j++)
				{
					if (m_IM->GetClientList()[j]->GetConnectionStatus())
					{
						m_Communication->Send(m_IM->GetClientList()[j]->GetEndpoint(), ServerPlayerPacket{ packet });
					}
				}

				//Send too all
				//for (size_t j = 0; j < m_IM->GetClientListSize(); j++)
				//{
				//	std::cout << "Send To: " << m_IM->GetClientList()[j]->GetID() << std::endl;

				//	if (m_IM->GetClientList()[j]->GetConnectionStatus())
				//	{
				//		m_Communication->Send(m_IM->GetClientList()[j]->GetEndpoint(), ServerPlayerPacket{ packet });
				//	}
				//}

			}
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}

