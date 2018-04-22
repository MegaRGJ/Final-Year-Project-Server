#include "stdafx.h"
#include "InterestManagement.h"


InterestManagement::InterestManagement()
{
	m_ClientListSize = 0; // value is currently used for ID.
	m_QuadTree = std::make_unique<QuadTree>(0, Rect(0, 0, 500, 500));
}

InterestManagement::~InterestManagement()
{
	for (size_t i = 0; i < m_ClientList.size(); i++)
	{
		delete m_ClientList[i];
	}
}

void InterestManagement::UpdateInterest()
{
	if (USE_QUADTREE_VS_AURA) // QuadTree // Grid
	{
		m_QuadTree->RemoveAll();

		for (size_t i = 0; i < m_ClientListSize; i++)
		{
			if (m_ClientList[i]->GetConnectionStatus())
			{
				m_QuadTree->Add(m_ClientList[i]);
			}
		}

		for (size_t i = 0; i < m_ClientListSize; i++)
		{
			if (m_ClientList[i]->GetConnectionStatus())
			{
				m_ClientList[i]->ClearSeenClients();
				std::vector<Client*> tempClients = m_QuadTree->GetClients(m_ClientList[i]);

				for (size_t i = 0; i < tempClients.size(); i++)
				{
					m_ClientList[i]->AddSeenClient(tempClients[i]);
				}
			}
		}
	}
	else //Euclidean Distance // Aura
	{
		for (size_t i = 0; i < m_ClientListSize; i++)
		{
			if (m_ClientList[i]->GetConnectionStatus())
			{
				Vector3 currentClient = *m_ClientList[i]->GetPos();
				Vector3 otherClient;
				m_ClientList[i]->ClearSeenClients();
		
				for (size_t j = 0; j < m_ClientListSize; j++)
				{
					if (m_ClientList[j]->GetConnectionStatus())
					{
						otherClient = *m_ClientList[j]->GetPos();
		
						if (EuclideanDistance(currentClient, otherClient) < AURA_DISTANCE)
						{
							m_ClientList[i]->AddSeenClient(m_ClientList[j]); // Adds a seen client
						}
					}
				}
			}
		}
	}
}

const std::vector<Client*> InterestManagement::GetClientList()
{
	return m_ClientList;
}

const int InterestManagement::GetClientListSize()
{
	return m_ClientListSize;
}

void InterestManagement::AddClient(Client * client)
{
	m_ClientList.push_back(client);
	m_ClientListSize++;
}

void InterestManagement::RemoveClient(Client * client)
{

	//m_ClientListSize--; Should not remove clients currently
}

float InterestManagement::EuclideanDistance(Vector3 &Pos1, Vector3 &Pos2)
{
	int d1 = abs(Pos1.X - Pos2.X);
	int d2 = abs(Pos1.Y - Pos2.Y);

	return d1 + d2;
}
