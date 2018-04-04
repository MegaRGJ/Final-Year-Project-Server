#pragma once

const int RECEIVE_BUFFER_SIZE = 128;
const int POSITION_ID = 1;
const int CONNECT_ID = 2;
const int DISCONNECT_ID = 3;

const double MS_INTERVAL = 1000;

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