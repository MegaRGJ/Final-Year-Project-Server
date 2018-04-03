#include "stdafx.h"
#include "Server.h"

Server::Server()
{

}

Server::~Server()
{

}

void Server::StartReceiveThread()
{
	boost::asio::io_service io_service;
	FinalYearProjectServer FinalYearProjectServer(io_service);
	io_service.run();
}

void Server::RunServer()
{
	try
	{
		std::cout << "Server Starting..." << std::endl;

		std::thread t(&StartReceiveThread);
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
				char* a = new char['1'];

				
				lag -= MS_INTERVAL;
			}
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}


void Server::HandlePacketData()
{

	//getpacketconnect
	//getpacketdisconect
	//getpacketpos
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