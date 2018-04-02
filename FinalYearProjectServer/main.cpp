#include "stdafx.h"
#include "FinalYearProjectServer.h"
#include <iostream>

int main()
{
	try
	{
		std::cout << "Server Starting..." << std::endl;
		boost::asio::io_service io_service;
		FinalYearProjectServer FinalYearProjectServer(io_service);
		io_service.run();

	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	system("pause");
	return 0;
}

