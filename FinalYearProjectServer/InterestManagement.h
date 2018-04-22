#pragma once
#include "Client.h"
#include "StructsAndConsts.h"
#include "QuadTree.h"

class InterestManagement
{
public:
	InterestManagement();
	~InterestManagement();

	void						UpdateInterest();
	const std::vector<Client*>	GetClientList();
	const int					GetClientListSize();
	void						AddClient(Client* client);
	void						RemoveClient(Client* client);

private:
	std::unique_ptr<QuadTree> m_QuadTree;
	std::vector<Client*> m_ClientList;
	int m_ClientListSize;
	static float EuclideanDistance(Vector3 &pos1, Vector3 &pos2);
};

