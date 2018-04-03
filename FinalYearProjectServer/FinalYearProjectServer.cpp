#include "stdafx.h"
#include <iostream>
#include "FinalYearProjectServer.h"
#include <chrono>

using namespace std::chrono;

FinalYearProjectServer::FinalYearProjectServer(boost::asio::io_service& io_service) :
	m_UDPSocket(io_service, udp::endpoint(udp::v4(), 4739))
{
	memebool = false;
	m_ClientListSize = 0;
	
	Receive();
}

FinalYearProjectServer::~FinalYearProjectServer()
{
	//io_service.stop();
	//service_thread.join();
}

void FinalYearProjectServer::Receive()
{
	std::cout << "Receiveing..." << std::endl;
	m_UDPSocket.async_receive_from
	(
		boost::asio::buffer(m_ReceiveBuffer),
		m_RemoteEndPoint,
		boost::bind
		(
			&FinalYearProjectServer::HandleReceive,
			this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred
		)
	);
	std::cout << "Receiveing... Out" << std::endl;
}

void FinalYearProjectServer::HandleReceive(const boost::system::error_code& error, std::size_t bytes_transferred)
{
	if (!error)
	{
		std::cout << "Received Packet." << std::endl;
		
		char receivedPacket[128];
		std::copy(std::begin(m_ReceiveBuffer), std::end(m_ReceiveBuffer), receivedPacket);

		int PacketID = Serialisation32Bit::DeserialisePacketType(receivedPacket);
		auto RemoteEndpoint = m_RemoteEndPoint;


		if (PacketID == POSITION_ID)
		{
			ClientPositionPacket packet = Serialisation32Bit::DeserialisePositionPacket(receivedPacket);
			//Change these to pointers later
			//UpdateClientPositionData(packet);
		}
		else if(PacketID = CONNECT_ID)
		{
			ClientConnectPacket packet = Serialisation32Bit::DeserialiseConnectPacket(receivedPacket);
			UpdateClientConnectData(packet);
		}
		else if(PacketID = DISCONNECT_ID)
		{
			ClientDisconnectPacket packet = Serialisation32Bit::DeserialiseDisconnectPacket(receivedPacket);

			UpdateClientDisconnectData(packet);
		}
		Receive();
	}
	else
	{
		std::cout << "Handle Receive Error." << std::endl;
	}
	
}

void FinalYearProjectServer::UpdateClientPositionData(ClientPositionPacket packet)
{
	m_ClientList[packet.ClientID].SetPos(packet.X, packet.Y, packet.Z);
	m_ClientList[packet.ClientID].SetRotationY(packet.Rotation);
}

void FinalYearProjectServer::UpdateClientConnectData(ClientConnectPacket packet)
{
	Client newClient = Client(m_RemoteEndPoint, packet, m_ClientListSize);

	m_ClientList.push_back(newClient);
	++m_ClientListSize;
}

void FinalYearProjectServer::UpdateClientDisconnectData(ClientDisconnectPacket packet)
{

	--m_ClientListSize;
}


void FinalYearProjectServer::Send(udp::endpoint remoteEndpoint, char *byteArray)
{
	std::cout << "Starting Send." << std::endl;
	
	m_UDPSocket.send_to(boost::asio::buffer(byteArray, sizeof(byteArray)), remoteEndpoint);
	std::cout << "Finsihed Send." << std::endl;
}
