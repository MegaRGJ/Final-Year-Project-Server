#pragma once

struct ClientPositionPacket
{
	int ClientID;
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