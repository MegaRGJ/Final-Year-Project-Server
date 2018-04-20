#pragma once
#pragma pack 1
#include "boost\asio.hpp"

const int RECEIVE_BUFFER_SIZE = 4096;
const int SEND_BUFFER_SIZE = 4096;
const int USERNAME_SIZE = 20;
const int PLAYER_ID = 1;
const int CONNECT_ID = 2;
const int DISCONNECT_ID = 3;
const int ACKNOWLEDGMENT_ID = 4;

const float AURA_DISTANCE = 50;

const double MS_INTERVAL = 16;

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
	char Username[USERNAME_SIZE];
};

struct ClientDisconnectPacket
{
	int ClientID;
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

struct ServerPacket
{
	virtual void Serialise(SendBuffer&) = 0;
};

struct ServerAcknowledgmentPacket : ServerPacket
{
	int ClientID;
	virtual void Serialise(SendBuffer&);
	
	ServerAcknowledgmentPacket() {}
	ServerAcknowledgmentPacket(int id)
	{
		ClientID = id;
	}
};

struct ServerPlayerPacket : ServerPacket
{
	int ClientID; 
	float X; 
	float Y; 
	float Z; 
	float Rotation; 
	char Username[USERNAME_SIZE];
	virtual void Serialise(SendBuffer&);

	ServerPlayerPacket() {}
	ServerPlayerPacket(int clientID, float x, float y, float z, float r, char username[])
	{
		ClientID = clientID;
		X = x;
		Y = y;
		Z = z;
		Rotation = r;
		strcpy_s(Username, username);
	}
};

struct Vector3
{
	float X;
	float Y;
	float Z;

	Vector3() {}
	Vector3(float x, float y, float z)
	{
		X = x;
		Y = y;
		Z = z;
	}
};