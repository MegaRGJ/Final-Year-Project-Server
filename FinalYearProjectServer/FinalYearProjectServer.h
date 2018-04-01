#include "boost\bind.hpp"
#include "boost\asio.hpp"
#pragma once

using boost::asio::ip::udp;

class FinalYearProjectServer
{
public:
	FinalYearProjectServer(boost::asio::io_service& io_service);
	~FinalYearProjectServer();

private:
	udp::socket m_UDPSocket;
	udp::endpoint m_RemoteEndPoint;
	std::array<char, 512> m_ReceiveBuffer;

	void Receive();
	void HandleReceive(const boost::system::error_code& error, std::size_t bytes_transferred);
};

