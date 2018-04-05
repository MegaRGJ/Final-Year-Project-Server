#include "stdafx.h"
#include "Server.h"

Server::Server()
{
	m_ClientListSize = 0;
}

Server::~Server()
{

}

void Server::RunServer()
{
	try
	{
		std::cout << "Server Starting..." << std::endl;

		std::thread t(&Server::StartReceiveThread, this);
		t.detach();

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

				HandlePacketData();

				
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

void Server::HandlePacketData()
{
	if (!m_Communication->IsConnectDataQueueEmpty())
	{
		UpdateConnectionData();
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

void Server::ConfirmConnectionPacketArrived()
{
	int id = *m_ClientList[m_ClientListSize].GetID();
	m_Communication->Send(m_ClientList[id].GetEndpoint(), ServerAcknowledgmentPacket {id});
}

//void FinalYearProjectServer::UpdateClientPositionData(ClientPositionPacket packet)
//{
//	m_ClientList[packet.ClientID].SetPos(packet.X, packet.Y, packet.Z);
//	m_ClientList[packet.ClientID].SetRotationY(packet.Rotation);
//}
//
//void FinalYearProjectServer::UpdateClientConnectData(ClientConnectPacket packet)
//{
//	Client newClient = Client(m_RemoteEndPoint, packet, m_ClientListSize);
//
//	m_ClientList.push_back(newClient);
//	++m_ClientListSize;
//}
//
//void FinalYearProjectServer::UpdateClientDisconnectData(ClientDisconnectPacket packet)
//{
//
//	--m_ClientListSize;
//}