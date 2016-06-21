#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>
#include "packet.h"
#include "Buffer.h"

#define PORT_NUMBER 25500
#define DATA_SIZE 500

class Net
{
private:
	WSADATA wsaData;

public:
	Net();
	~Net();
	SOCKET openSocket();
	void closeSocket(SOCKET);
	sockaddr_in generateSocketAddr();
	sockaddr_in generateSocketAddr(std::string ipAddr);
	sockaddr_in getPeerInfo(SOCKET);
	void bindListenSocket(SOCKET listenSocket, sockaddr_in sockAddr);
	void openListenSocket(SOCKET listenSocket);
	bool connectTo(SOCKET, sockaddr_in sockAddr);
	bool acceptConnection(SOCKET listen, SOCKET& remote, sockaddr_in& remoteAddr);
	int recvData(SOCKET, Buffer<SerializedPacket>&);
	void sendData(SOCKET, Buffer<SerializedPacket>&);
	void printSockAddrInfo(sockaddr_in&);
};
