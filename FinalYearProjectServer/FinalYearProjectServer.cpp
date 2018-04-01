#include "stdafx.h"
#include <iostream>
#include "FinalYearProjectServer.h"

FinalYearProjectServer::FinalYearProjectServer(boost::asio::io_service& io_service) :
	m_UDPSocket(io_service, udp::endpoint(udp::v4(), 4739))
{
	Receive();
}
FinalYearProjectServer::~FinalYearProjectServer()
{

}

void FinalYearProjectServer::Receive()
{
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
		int ayy = 1;
		auto meme = m_ReceiveBuffer;
		auto meme2 = m_RemoteEndPoint;
		std::cout << "meme" << std::endl;

		Receive();
	}
}
