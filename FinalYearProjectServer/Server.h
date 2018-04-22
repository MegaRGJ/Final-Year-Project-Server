#pragma once
#include <iostream>
#include <thread>
#include "Timer.h"
#include "boost\asio.hpp"
#include "Commuication.h"
#include "InterestManagement.h"

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
	InterestManagement* m_IM;
	std::thread* m_ReceiveThread;
	std::thread* m_InputThread;

	void HandleReceivedPacketData();
	void SendPositionalPacketData();

	void UpdateConnectionData();
	void UpdateClientPositionData();
	void UpdateDisconnectData();
	void HandleInterestInput();
	void HandleIPAddress();
	void ConfirmAcknowledgmentPacketArrived(int clientid);

};

