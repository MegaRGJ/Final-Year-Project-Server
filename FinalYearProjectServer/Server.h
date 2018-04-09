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
	void StartInputThread();
private:
	Communication* m_Communication;
	std::thread* m_ReceiveThread;
	std::thread* m_InputThread;

	std::vector<Client*> m_ClientList;
	int m_ClientListSize;

	void HandleReceivedPacketData();
	void SendPositionalPacketData();

	void UpdateConnectionData();
	void UpdateClientPositionData();
	void UpdateDisconnectData();

	void ConfirmAcknowledgmentPacketArrived(int clientid);

};

