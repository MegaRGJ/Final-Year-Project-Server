#include "stdafx.h"
#include <iostream>
#include "Commuication.h"
#include <chrono>

using namespace std::chrono;

Communication::Communication(boost::asio::io_service& io_service) :
	m_UDPSocket(io_service, udp::endpoint(udp::v4(), 4739))
{
	
	Receive();
}

Communication::~Communication()
{
	m_UDPSocket.close();
}

void Communication::Receive()
{
	std::cout << "Receiveing..." << std::endl;
	m_UDPSocket.async_receive_from
	(
		boost::asio::buffer(m_ReceiveBuffer),
		m_RemoteEndPoint,
		boost::bind
		(
			&Communication::HandleReceive,
			this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred
		)
	);
	std::cout << "Receiveing... Out" << std::endl;
}

void Communication::HandleReceive(const boost::system::error_code& error, std::size_t bytes_transferred)
{
	if (!error)
	{
		std::cout << "Received Packet." << std::endl;
		
		char receivedPacket[128];
		std::copy(std::begin(m_ReceiveBuffer), std::end(m_ReceiveBuffer), receivedPacket);

		int PacketID = Serialisation32Bit::DeserialisePacketType(receivedPacket);

		//Use function table thing maybe?

		if (PacketID == POSITION_ID)
		{
			ClientPositionPacket packet = Serialisation32Bit::DeserialisePositionPacket(receivedPacket);
			m_PositionPacketQueue.push(packet);
		}
		else if(PacketID = CONNECT_ID)
		{
			ClientConnectPacket packet = Serialisation32Bit::DeserialiseConnectPacket(receivedPacket);
			
			ConnectData data(m_RemoteEndPoint, packet);
			m_ConnectDataQueue.push(data);
		}
		else if(PacketID = DISCONNECT_ID)
		{
			ClientDisconnectPacket packet = Serialisation32Bit::DeserialiseDisconnectPacket(receivedPacket);
			m_DisconnectPacketQueue.push(packet);
		}
		Receive();
	}
	else
	{
		std::cerr << "Handle Receive Error." << std::endl;
	}
}

void Communication::Send(udp::endpoint remoteEndpoint, const ServerPacket& packet)
{
	std::cout << "Starting Send." << std::endl;

	//clear data to be sent
	m_SendBufferSize = 0;

	//create thing that gives other things way to tell us what data to send
	SendBuffer BufferAdapter;
	BufferAdapter.Buffer = m_SendBuffer;
	BufferAdapter.size = &m_SendBufferSize;

	//serialise packet, giving it thing which allows it to put data in our m_SendBuffer
	packet.Serialise(BufferAdapter);

	//send data now stored in m_SendBuffer
	m_UDPSocket.async_send_to(boost::asio::buffer(m_SendBuffer, m_SendBufferSize), remoteEndpoint,
		boost::bind
		(
			&Communication::HandleSend,
			this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred
		));


	std::cout << "Finsihed Send." << std::endl;
}

void Communication::HandleSend(const boost::system::error_code& error, std::size_t bytes_transferred)
{
	if (!error)
	{

	}
	else
	{
		std::cerr << "Handle Send Error." << std::endl;
	}
}

ClientPositionPacket Communication::GetClientPositionPacket()
{
	if (m_PositionPacketQueue.isEmpty())
	{
		throw std::logic_error("Position Packet Queue is Empty.");
	}
	return m_PositionPacketQueue.pop();
}

std::vector<ClientPositionPacket> Communication::GetAllClientPositionPackets()
{
	if (m_PositionPacketQueue.isEmpty())
	{
		throw std::logic_error("Position Packet Queue is Empty.");
	}

	return m_PositionPacketQueue.popAll();
}

ConnectData Communication::GetConnectData()
{
	if (m_ConnectDataQueue.isEmpty())
	{
		throw std::logic_error("Connect Packet Queue is Empty.");
	}

	return m_ConnectDataQueue.pop();
}

std::vector<ConnectData> Communication::GetAllConnectData()
{
	if (m_ConnectDataQueue.isEmpty())
	{
		throw std::logic_error("Connect Packet Queue is Empty");
	}

	return m_ConnectDataQueue.popAll();
}

ClientDisconnectPacket Communication::GetClientDisconnectPacket()
{
	if (m_DisconnectPacketQueue.isEmpty())
	{
		throw std::logic_error("Disconnect Packet Queue is Empty");
	}

	return m_DisconnectPacketQueue.pop();
}

std::vector<ClientDisconnectPacket> Communication::GetAllClientDisconnectPackets()
{
	if (m_DisconnectPacketQueue.isEmpty())
	{
		std::logic_error("Disconnect Packet Queue is Empty");
	}

	return m_DisconnectPacketQueue.popAll();
}

bool Communication::IsConnectDataQueueEmpty()
{
	return m_ConnectDataQueue.isEmpty();
}

bool Communication::IsPositionPacketQueueEmpty()
{
	return m_PositionPacketQueue.isEmpty();
}

bool Communication::IsDisconnectPacketQueueEmpty()
{
	return m_DisconnectPacketQueue.isEmpty();
}