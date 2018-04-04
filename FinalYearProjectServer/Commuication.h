#include "boost\bind.hpp"
#include "boost\asio.hpp"
#include "Serialisation32Bit.h"
#include "Client.h"
#include "Timer.h"
#include "Queue.h"
#include "StructsAndConsts.h"
#pragma once

using boost::asio::ip::udp;

class Communication
{
public:
	Communication(boost::asio::io_service& io_service);
	~Communication();
	
	void Send(udp::endpoint remoteEndpoint, char* byteArray);

	ClientPositionPacket GetClientPositionPacket();
	std::vector<ClientPositionPacket> GetAllClientPositionPackets();

	ClientConnectPacket GetClientConnectPacket();
	std::vector<ClientConnectPacket> GetAllClientConnectPackets();

	ClientDisconnectPacket GetClientDisconnectPacket();
	std::vector<ClientDisconnectPacket> GetAllClientDisconnectPackets();
	//GET PACKETS LIKE IN CLIENT

private:

	Queue<ClientPositionPacket> m_PositionPacketQueue;
	Queue<ClientConnectPacket> m_ConnectPacketQueue;
	Queue<ClientDisconnectPacket> m_DisconnectPacketQueue;

	udp::socket m_UDPSocket;
	udp::endpoint m_RemoteEndPoint;
	char m_ReceiveBuffer[RECEIVE_BUFFER_SIZE];
	char m_SendBuffer[RECEIVE_BUFFER_SIZE];

	void Receive();
	void HandleReceive(const boost::system::error_code& error, std::size_t bytes_transferred);

	void HandleSend(const boost::system::error_code& error, std::size_t bytes_transferred);
};

