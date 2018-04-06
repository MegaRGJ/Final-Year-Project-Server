#pragma once
#include "boost\asio.hpp"

const int RECEIVE_BUFFER_SIZE = 128;
const int SEND_BUFFER_SIZE = 128;
const int POSITION_ID = 1;
const int CONNECT_ID = 2;
const int DISCONNECT_ID = 3;
const int ACKNOWLEDGMENT_ID = 4;

const double MS_INTERVAL = 1000;

struct SendBuffer
{
	char* Buffer;
	int* size;
};

struct ClientPositionPacket
{
	int ClientID = 0;
	float X = 0;
	float Y = 0;
	float Z = 0;
	float Rotation = 0;
};

struct ClientConnectPacket
{
	char Username[20];
};

struct ClientDisconnectPacket
{
	int ClientID;
};

struct ServerPacket
{
	virtual void Serialise(SendBuffer&) const = 0;
};

struct ServerAcknowledgmentPacket : ServerPacket
{
	int ClientID;
	virtual void Serialise(SendBuffer&) const;
	
	ServerAcknowledgmentPacket(int id)
	{
		ClientID = id;
	}
};

struct ConnectData
{
	ClientConnectPacket Packet;
	boost::asio::ip::udp::endpoint EndPoint;

	ConnectData() {}
	ConnectData(boost::asio::ip::udp::endpoint endpoint, ClientConnectPacket packet)
	{
		EndPoint = endpoint;
		Packet = packet;
	}
};


struct Vector3
{
	float X;
	float Y;
	float Z;

	Vector3(float x, float y, float z)
	{
		X = x;
		Y = y;
		Z = z;
	}
};