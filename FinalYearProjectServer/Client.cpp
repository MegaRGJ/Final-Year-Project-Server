#include "stdafx.h"
#include "Client.h"

Client::Client(udp::endpoint clientEndPoint, ClientConnectPacket packet, int clientID)
{
	m_EndPoint = clientEndPoint;
	strncpy_s(m_Username, packet.Username, 20);

	m_Position = new Vector3(0, 0, 0);
	m_RotationY = new float(0);
	m_ClientID = new int(clientID);
	//Add a unquie ID
}

Client::~Client()
{
	delete m_Position;
	delete m_RotationY;
	delete m_ClientID;
}

const Vector3* Client::GetPos()
{
	return m_Position;
}

void Client::SetPos(float x, float y, float z)
{
	m_Position->X = x;
	m_Position->Y = y;
	m_Position->Z = z;
}

const float* Client::GetRotationY()
{
	return m_RotationY;
}

void Client::SetRotationY(float r)
{
	*m_RotationY = r;
}

const int* Client::GetID()
{
	return m_ClientID;
}

const udp::endpoint Client::GetEndpoint()
{
	return m_EndPoint;
}

const char* Client::GetUsername()
{
	return m_Username;
}