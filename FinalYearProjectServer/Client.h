#pragma once
#include "boost\asio.hpp"
#include "StructsAndConsts.h"
using boost::asio::ip::udp;

class Client
{
	
public:
	Client(udp::endpoint clientEndPoint, ClientConnectPacket packet, int clientID);
	~Client();

	const Vector3*				GetPos();
	void						SetPos(float x, float y, float z);
	const float*				GetRotationY();
	void						SetRotationY(float r);
	const int*					GetID();
	const udp::endpoint			GetEndpoint();
	const char*					GetUsername();
private:
	udp::endpoint m_EndPoint;
	char m_Username[20];
	Vector3* m_Position;
	float* m_RotationY;
	int* m_ClientID;

	//Client SeenBy[0];
};

