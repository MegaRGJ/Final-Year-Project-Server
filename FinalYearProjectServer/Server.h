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
	void HandlePacketData();
private:
	Communication* m_Communication;

	std::vector<Client> m_ClientList; //May need to be made thread safe.
	int m_ClientListSize;

	void UpdateConnectionData();
	void UpdateDisconnectData();

	void ConfirmConnectionPacketArrived();
};

