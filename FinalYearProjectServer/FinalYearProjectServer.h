#include "boost\bind.hpp"
#include "boost\asio.hpp"
#include "Serialisation32Bit.h"
#include "Client.h"
#include "Timer.h"
#include "Queue.h"
#pragma once

using boost::asio::ip::udp;
const int RECEIVE_BUFFER_SIZE = 128;
const int POSITION_ID = 1;
const int CONNECT_ID = 2;
const int DISCONNECT_ID = 3;

const double MS_INTERVAL = 1000;

class FinalYearProjectServer
{
public:
	FinalYearProjectServer(boost::asio::io_service& io_service);
	~FinalYearProjectServer();
	
	void Send(udp::endpoint remoteEndpoint, char* byteArray);

	Queue<ClientPositionPacket> GetClientPositionPackets();
	//GET PACKETS LIKE IN CLIENT

private:
	std::vector<Client> m_ClientList;
	int m_ClientListSize;

	udp::socket m_UDPSocket;
	udp::endpoint m_RemoteEndPoint;
	char m_ReceiveBuffer[RECEIVE_BUFFER_SIZE];
	char m_SendBuffer[RECEIVE_BUFFER_SIZE];

	void Receive();
	void HandleReceive(const boost::system::error_code& error, std::size_t bytes_transferred);

	void HandleSend(const boost::system::error_code& error, std::size_t bytes_transferred);
	
	void UpdateClientPositionData(ClientPositionPacket packet);
	void UpdateClientConnectData(ClientConnectPacket packet);
	void UpdateClientDisconnectData(ClientDisconnectPacket packet);
};

