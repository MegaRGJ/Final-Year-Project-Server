#include "boost\bind.hpp"
#include "boost\asio.hpp"
#include "Serialisation32Bit.h"
#include "Client.h"
#pragma once

using boost::asio::ip::udp;
const int RECEIVE_BUFFER_SIZE = 128;
const int POSITION_ID = 1;
const int CONNECT_ID = 2;
const int DISCONNECT_ID = 3;

class FinalYearProjectServer
{
public:
	FinalYearProjectServer(boost::asio::io_service& io_service);
	~FinalYearProjectServer();

private:
	std::vector<Client> m_ClientList;
	int m_ClientListSize;

	udp::socket m_UDPSocket;
	udp::endpoint m_RemoteEndPoint;
	std::array<char, RECEIVE_BUFFER_SIZE> m_ReceiveBuffer;

	void Receive();
	void HandleReceive(const boost::system::error_code& error, std::size_t bytes_transferred);
};

