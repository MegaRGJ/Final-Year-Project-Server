#include "stdafx.h"
#include "QuadTree.h"


QuadTree::QuadTree()
{
	
}

QuadTree::QuadTree(int level, Rect bounds)
{
	m_Level = level;
	m_Bounds = bounds;
}

QuadTree::~QuadTree()
{

}

void QuadTree::Add(Client*& client)
{
	if (m_Nodes[0] != nullptr)
	{
		int i = GetIndex(client);

		if (i != -1)
		{
			m_Nodes[i]->Add(client);
			//std::cout << "Added 1: " << client->GetID() << " Node : " << i << std::endl;
			return;
		}
	}

	m_ClientList.push_back(client);

	if ((m_ClientList.size() > max_objects) && (m_Level < max_levels))
	{
		if (m_Nodes[0] == nullptr)
		{
			Split();
		}

		int i = 0;
		while (i < m_ClientList.size())
		{
			int j = GetIndex(m_ClientList[i]);

			if (j != -1)
			{
				m_Nodes[j]->Add(m_ClientList[i]);
				//std::cout << "Added 2: " << *m_ClientList[i]->GetID() << " Node : " << j << std::endl;
				m_ClientList.erase(m_ClientList.begin() + i);
			}
			else
			{
				i++;
			}
		}
	}
}

void QuadTree::RemoveAll()
{
	m_ClientList.clear();

	for (size_t i = 0; i < 4; ++i)
	{
		if (m_Nodes[i] != nullptr)
		{
			m_Nodes[i]->RemoveAll();
			m_Nodes[i] = nullptr;
		}
	}
}

std::vector<Client*> QuadTree::GetClients(Client * client)
{
	int i = GetIndex(client);
	std::vector<Client*> clients;

	if (i != -1 && m_Nodes[0] != nullptr)
	{
		std::vector<Client*> tempClients = m_Nodes[i]->GetClients(client);
		clients.insert(clients.end(), tempClients.begin(), tempClients.end());
	}

	clients.insert(clients.end(), m_ClientList.begin(), m_ClientList.end());
	return clients;
}

int QuadTree::GetIndex(Client * client)
{
	int index = -1;

	float verticalMidpoint = m_Bounds.X + (m_Bounds.Width / 2);
	float horizontalMidpoint = m_Bounds.Y + (m_Bounds.Height / 2);

	//Checks if it fits in the top
	bool canFitTopQuad = ((client->GetBounds().Y < horizontalMidpoint) && ((client->GetBounds().Y + client->GetBounds().Height) < horizontalMidpoint));
	//Checks if it fits in the bottom
	bool canFitBottomQuad = (client->GetBounds().Y > horizontalMidpoint);
	//Checks if it fits in the left
	if ((client->GetBounds().X < verticalMidpoint) && ((client->GetBounds().X + client->GetBounds().Width) < verticalMidpoint))
	{
		if (canFitTopQuad)
		{
			index = 1;
		}
		else if (canFitBottomQuad)
		{
			index = 2;
		}
	}
	//Checks if it fits in the right
	else if (client->GetBounds().X > verticalMidpoint)
	{
		index = 3;
	}
	return index;
}

void QuadTree::Split()
{
	float subNodeWidth = m_Bounds.X / 2;
	float subNodeHeight = m_Bounds.Y / 2;
	float x = m_Bounds.X;
	float y = m_Bounds.Y;

	m_Nodes[0] = std::make_unique<QuadTree>(m_Level + 1, Rect(x + subNodeWidth, y, subNodeWidth, subNodeHeight));
	m_Nodes[1] = std::make_unique<QuadTree>(m_Level + 1, Rect(x, y, subNodeWidth, subNodeHeight));
	m_Nodes[2] = std::make_unique<QuadTree>(m_Level + 1, Rect(x, y + subNodeHeight, subNodeWidth, subNodeHeight));
	m_Nodes[3] = std::make_unique<QuadTree>(m_Level + 1, Rect(x + subNodeWidth, y + subNodeHeight, subNodeWidth, subNodeHeight));
}