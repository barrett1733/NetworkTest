#pragma once
#include "net.h"
#include "PacketHandler.h"
#include "ThreadWrapper.h"
#include <mutex>
#include <condition_variable>

class ClientConnection : public Net
{
public:
	enum ConnectionStatus
	{
		CLOSED,	// Connection does not have client
		OPEN	// Connection has client
	};
private:
	SOCKET clientSocket;
	ConnectionStatus status;
	Buffer<SerializedPacket> recvBuf;
public:
	ClientConnection();
	Buffer<SerializedPacket> getRecvBuffer();
	void recieveData();
	void sendData(Buffer<SerializedPacket>&);
	void setSocket(SOCKET);
	SOCKET getSocket();
	void setStatus(ConnectionStatus);
	ConnectionStatus getStatus();
};

class ClientConnectionThread : public ClientConnection, public Threaded
{
	std::mutex mtx;
	std::condition_variable cvWait;
public:
	void setStatus(ConnectionStatus);
	void wakeup();
	void sleep();
	void run();
};
