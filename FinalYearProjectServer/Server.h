#pragma once
#include <iostream>
#include <thread>
#include "Timer.h"
#include "atltime.h" // GetCurrentTime
#include "boost\asio.hpp"
#include "FinalYearProjectServer.h"

class Server
{
public:
	Server();
	~Server();

	void RunServer();
	void StartReceiveThread();
	void HandlePacketData();
};

