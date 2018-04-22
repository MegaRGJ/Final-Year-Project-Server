#pragma once
#include "boost\asio.hpp"
#include "StructsAndConsts.h"
#include <algorithm>
using boost::asio::ip::udp;

class Client
{
	
public:
	Client(udp::endpoint clientEndPoint, ClientConnectPacket packet, int clientID);
	~Client();
	const bool*					GetConnectionStatus();
	void						SetConnectionStatus(bool var);

	const std::vector<Client*>	GetSeenClients();
	void						ClearSeenClients();
	void						AddSeenClient(Client* client);
	void						RemoveSeenClient(Client* client);
	const Vector3*				GetPos();
	void						SetPos(float x, float y, float z);
	const float*				GetRotationY();
	void						SetRotationY(float r);
	const int*					GetID();
	const udp::endpoint			GetEndpoint();
	const char*					GetUsername();
	const Rect					GetBounds();
private:
	udp::endpoint m_EndPoint;
	char m_Username[20];
	Vector3* m_Position;
	float* m_RotationY;
	int* m_ClientID;
	bool* m_Connected;
	Rect* m_Bound;

	int IndexBinarySearch(std::vector<Client*> &SeenBy, int start, int end, int id);
	std::vector<Client*>* m_Seen;
};

