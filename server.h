#pragma once
#include "net.h"
#include "Packet.h"
#include "PacketHandler.h"
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include "Options.h"
#include "ClientConnection.h"
#include <functional>

#define MAX_CONNECTIONS_OPEN 20

class Server : public Net, public Threaded
{
	ClientConnectionThread clientConnectionPool[MAX_CONNECTIONS_OPEN];
	SOCKET listenSocket;
	WSADATA wsaData;
	SOCKET remoteSocket;
	sockaddr_in remoteAddr;
	OptionsHandler optsHandle;
	std::vector<std::thread> clientThreads;
	void acceptConnection();
	int findClosedConnection();

public:
	Server();
	~Server();
	void run();
	void sendData();
};