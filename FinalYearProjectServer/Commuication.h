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
	
	void Send(udp::endpoint remoteEndpoint, ServerPacket& packet);

	ClientPositionPacket GetClientPositionPacket();
	std::vector<ClientPositionPacket> GetAllClientPositionPackets();
	bool IsPositionPacketQueueEmpty();

	ConnectData GetConnectData();
	std::vector<ConnectData> GetAllConnectData();
	bool IsConnectDataQueueEmpty();

	ClientDisconnectPacket GetClientDisconnectPacket();
	std::vector<ClientDisconnectPacket> GetAllClientDisconnectPackets();
	bool IsDisconnectPacketQueueEmpty();
private:

	Queue<ConnectData> m_ConnectDataQueue;
	Queue<ClientPositionPacket> m_PositionPacketQueue;
	Queue<ClientDisconnectPacket> m_DisconnectPacketQueue;

	udp::socket m_UDPSocket;
	udp::endpoint m_RemoteEndPoint;
	char m_ReceiveBuffer[RECEIVE_BUFFER_SIZE];
	char m_SendBuffer[SEND_BUFFER_SIZE];
	int m_SendBufferSize;

	void Receive();
	void HandleReceive(const boost::system::error_code& error, std::size_t bytes_transferred);

	void HandleSend(const boost::system::error_code& error, std::size_t bytes_transferred);
};

