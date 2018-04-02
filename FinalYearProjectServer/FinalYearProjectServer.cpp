#include "stdafx.h"
#include <iostream>
#include "FinalYearProjectServer.h"

FinalYearProjectServer::FinalYearProjectServer(boost::asio::io_service& io_service) :
	m_UDPSocket(io_service, udp::endpoint(udp::v4(), 4739))
{
	m_ClientListSize = 0;
	Receive();
}
FinalYearProjectServer::~FinalYearProjectServer()
{

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
}

void FinalYearProjectServer::HandleReceive(const boost::system::error_code& error, std::size_t bytes_transferred)
{
	if (!error)
	{
		std::cout << "Received Packet." << std::endl;
		char ReceivedPacket[128];

		std::array<char, RECEIVE_BUFFER_SIZE> meme = m_ReceiveBuffer;

		std::copy(std::begin(meme), std::end(meme), ReceivedPacket);

		int PacketID = Serialisation32Bit::DeserialisePacketType(ReceivedPacket);
		auto RemoteEndpoint = m_RemoteEndPoint;

		if (PacketID == POSITION_ID)
		{
			ClientPositionPacket Packet = Serialisation32Bit::DeserialisePositionPacket(ReceivedPacket);
			
			m_ClientList[Packet.ClientID].SetPos(Packet.X, Packet.Y, Packet.Z);
			m_ClientList[Packet.ClientID].SetRotationY(Packet.Rotation);

		}
		else if(PacketID = CONNECT_ID)
		{
			ClientConnectPacket packet = Serialisation32Bit::DeserialiseConnectPacket(ReceivedPacket);
			Client newClient = Client(m_RemoteEndPoint, packet, m_ClientListSize);
			
			m_ClientList.push_back(newClient);
			++m_ClientListSize;
		}
		else if(PacketID = DISCONNECT_ID)
		{
			ClientDisconnectPacket Packet = Serialisation32Bit::DeserialiseDisconnectPacket(ReceivedPacket);

			--m_ClientListSize;
		}

		
		Receive();
	}
	else
	{
		std::cout << "Handle Receive Error." << std::endl;
	}
}

