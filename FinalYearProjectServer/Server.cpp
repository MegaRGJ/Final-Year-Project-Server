#include "stdafx.h"
#include "Server.h"

Server::Server()
{
	m_ClientListSize = 0;
}

Server::~Server()
{
	delete m_Communication;
	delete ReceiveThread;
}

void Server::RunServer()
{
	try
	{
		std::cout << "Server Starting..." << std::endl;

		ReceiveThread = new std::thread(&Server::StartReceiveThread, this);
		ReceiveThread->detach();

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
				std::cout << "Frame. " << lag << std::endl;

				HandleReceivedPacketData();
				
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
		Client client = Client(connectionData[i].EndPoint, connectionData[i].Packet, m_ClientListSize);
		m_ClientList.push_back(client);
		ConfirmConnectionPacketArrived();
		++m_ClientListSize;
	}
}

void Server::UpdateDisconnectData()
{
	std::vector<ClientDisconnectPacket> disconnectPacket = m_Communication->GetAllClientDisconnectPackets();

	for (size_t i = 0; i < disconnectPacket.size(); i++)
	{
		m_ClientList[disconnectPacket[i].ClientID].SetConnectionStatus(false);
		//--m_ClientListSize; Can't make the list small due to not reallocating id locations
		// even so, this would not be the correct thing to do anyway need to make a system.
		// need to send back a real id linked to location in arr.
	}
}

void Server::UpdateClientPositionData()
{
	std::vector<ClientPositionPacket> positionPackets = m_Communication->GetAllClientPositionPackets();
	
	for (size_t i = 0; i < positionPackets.size(); i++)
	{
		if (m_ClientList[i].GetConnectionStatus())
		{
			m_ClientList[positionPackets[i].ClientID].SetPos(positionPackets[i].X, positionPackets[i].Y, positionPackets[i].Z);
			m_ClientList[positionPackets[i].ClientID].SetRotationY(positionPackets[i].Rotation);
		}
	}

}

void Server::ConfirmConnectionPacketArrived()
{
	int id = *m_ClientList[m_ClientListSize].GetID();
	 (m_ClientList[id].GetEndpoint(), ServerAcknowledgmentPacket{ id });
}

void Server::SendPositionalPacketData()
{
	for (size_t i = 0; i < m_ClientList.size; i++)
	{
		if (m_ClientList[i].GetConnectionStatus())
		{
			for (size_t i = 0; i < m_ClientList[i]; i++)
			{
				m_Communication->Send(m_ClientList[i].GetEndpoint(), )
			}

				
		}
	}
}

