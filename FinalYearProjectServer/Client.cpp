#include "stdafx.h"
#include "Client.h"

Client::Client(udp::endpoint clientEndPoint, ClientConnectPacket packet, int clientID)
{
	m_EndPoint = clientEndPoint;
	memcpy(m_Username, packet.Username, USERNAME_SIZE);

	m_Position = new Vector3(0, 0, 0);
	m_RotationY = new float(0);
	m_ClientID = new int(clientID);
	m_Connected = new bool(true);
	m_Seen = new std::vector<Client*>();
}

Client::~Client()
{
	delete m_Position;
	delete m_RotationY;
	delete m_ClientID;
	delete m_Connected;
	delete m_Seen;
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

const std::vector<Client*> Client::GetSeenClients()
{
	return *m_Seen;
}

void Client::AddSeenClient(Client* client)
{
	m_Seen->push_back(client);
	std::sort(m_Seen->begin(), m_Seen->end(), [](const auto& a, const auto& b) {
		return (a->GetID() < b->GetID());
	});
}

void Client::ClearSeenClients()
{
	m_Seen->clear();
}

void Client::RemoveSeenClient(Client* client)
{
	int clientID = *client->GetID();
	int index = IndexBinarySearch(*m_Seen, 0, m_Seen->size(), clientID);

	if (index != -1)
	{
		m_Seen->erase(m_Seen->begin() + index);
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