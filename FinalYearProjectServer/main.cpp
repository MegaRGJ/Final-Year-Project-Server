#include "stdafx.h"
#include "Server.h"
#include <iostream>




int main()
{
	Server server;
	server.RunServer();

	server.~Server();

	std::cout << "Server Closing!" << std::endl;
	system("pause");
	return 0;
}


