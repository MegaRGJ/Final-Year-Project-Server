#pragma once
#include <iostream>
#include <thread>
#include "Timer.h"
#include "atltime.h" // GetCurrentTime
#include "boost\asio.hpp"
#include "Commuication.h"

class Server
{
public:
	Server();
	~Server();

	void RunServer();
	void StartReceiveThread();

private:
	Communication* m_Communication;
	std::thread* ReceiveThread;

	std::vector<Client> m_ClientList; //May need to be made thread safe.
	int m_ClientListSize;

	void HandleReceivedPacketData();
	void SendPositionalPacketData();

	void UpdateConnectionData();
	void UpdateClientPositionData();
	void UpdateDisconnectData();

	void ConfirmConnectionPacketArrived();

};

