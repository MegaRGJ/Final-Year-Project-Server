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
	return *m_SeenBy;
}

void Client::AddSeenByClient(Client* client)
{
	m_SeenBy->push_back(client);
	std::sort(m_SeenBy->begin(), m_SeenBy->end(), [](const auto& a, const auto& b) {
		return (a->GetID() < b->GetID());
	});
}

void Client::RemoveSeenByClient(Client* client)
{
	int clientID = *client->GetID();
	int index = IndexBinarySearch(*m_SeenBy, 0, m_SeenBy->size(), clientID);

	if (index != -1)
	{
		m_SeenBy->erase(m_SeenBy->begin() + index);
	}
	else
	{
		//throw std::logic_error("Could not remove, client not found!");
	}
}

int Client::IndexBinarySearch(std::vector<Client*> &SeenBy, int start, int end, int id)
{
	while (start <= end)
	{
		int i = start + (end - start) / 2;
		int clientID = *SeenBy[i]->GetID();
		//Is it in the middle?
		if (clientID == id)
		{
			return i;
		}

		//If greater don't search left side
		if (clientID < id)
		{
			start = i + 1;
		}
		else //If smaller don't search right side
		{
			end = i - 1;
		}
	}
	return -1;
}