#pragma once
#include "net.h"
#include "packet.h"
#include "PacketHandler.h"

class Client : public Net, public PacketHandler
{
	SOCKET clientSocket;
public:
	Client() { clientSocket = openSocket(); }
	~Client() { closesocket(clientSocket); }
	bool connectTo(std::string ipAddr);
	void sendData(std::string clientId, std::string data);
};
