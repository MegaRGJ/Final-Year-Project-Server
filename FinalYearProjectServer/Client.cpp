#include "stdafx.h"
#include "Client.h"

Client::Client(udp::endpoint clientEndPoint, ClientConnectPacket packet, int clientID)
{
	m_EndPoint = clientEndPoint;
	strncpy_s(m_Username, packet.Username, 20);

	m_Position = new Vector3(0, 0, 0);
	m_RotationY = new float(0);
	m_ClientID = new int(clientID);
	m_Connected = new bool(true);
	m_SeenBy = new std::vector<Client*>(10);
}

Client::~Client()
{
	delete m_Position;
	delete m_RotationY;
	delete m_ClientID;
	delete m_Connected;
	delete m_SeenBy;
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

const bool* Client::GetConnectionStatus()
{
	return m_Connected;
}

void Client::SetConnectionStatus(bool var)
{
	*m_Connected = var;
}

const std::vector<Client*> Client::GetSeenByClients()
{
	return; // Return seen clients too the Server SendPositionalPacketData
}

void Client::AddSeenByClient(Client* client)
{
	m_SeenBy->push_back(client);
}

void Client::RemoveSeenByClient(Client* client)
{
	//m_SeenBy->erase()

	//Need to make this a find based on something in the client.
	//This will then be able to get moved out to the main fyp octree.
}