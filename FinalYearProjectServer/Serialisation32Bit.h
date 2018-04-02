#include <iostream>
#include "Structs.h"
#pragma once

class Serialisation32Bit
{
public:
	static int DeserialisePacketType(char* byteArray);

	void SerialiseConnectData();
	void SerialiseDisconnetData();
	void SerialisePositionData();

	static ClientPositionPacket DeserialisePositionPacket(char* byteArray);
	static ClientConnectPacket DeserialiseConnectPacket(char* byteArray);
	static ClientDisconnectPacket DeserialiseDisconnectPacket(char* byteArray);

private:

};

