#pragma once
#include "StructsAndConsts.h"
#include "Client.h"
#include <iostream>
#include <memory>

class QuadTree
{
public:
	QuadTree();
	QuadTree(int level, Rect bounds);
	~QuadTree();

	void Add(Client *& client);
	void RemoveAll();
	std::vector<Client*> GetClients(Client * client);
	int GetIndex(Client * client);
	void Split();


private:
	//Maybe move these out.
	int max_objects = 2;
	int max_levels = 4;

	int m_Level;
	Rect m_Bounds;
	std::vector<Client*> m_ClientList;
	std::unique_ptr<QuadTree> m_Nodes[4];

};

