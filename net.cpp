#include "net.h"

using namespace std;

Net::Net()
{
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		cerr << "WSAStartup failed.\n";
		exit(1);
	}
}

Net::~Net()
{
	if (WSACleanup() != 0)
	{
		cerr << WSAGetLastError();
	}
}

SOCKET Net::openSocket()
{
	SOCKET hSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (hSocket == INVALID_SOCKET)
	{
		cerr << WSAGetLastError();
	}
	return hSocket;
}

void Net::closeSocket(SOCKET socket)
{
	closesocket(socket);
}

sockaddr_in Net::getPeerInfo(SOCKET socket)
{
	sockaddr* info = NULL;
	int infoSize = sizeof(sockaddr);
	if (getpeername(socket, info, &infoSize) == SOCKET_ERROR)
	{
		cerr << "Get Peer Name - Error: " << WSAGetLastError() << endl;
		return generateSocketAddr("0.0.0.0");
	}
	else
		return *(struct sockaddr_in*)(info);
}

sockaddr_in Net::generateSocketAddr()
{
	return generateSocketAddr(INADDR_ANY);
}

sockaddr_in Net::generateSocketAddr(string ipAddr)
{
	sockaddr_in sockAddr;

	sockAddr.sin_family = AF_INET;
	sockAddr.sin_port = htons(PORT_NUMBER);
	inet_pton(AF_INET, ipAddr.c_str(), &(sockAddr.sin_addr));
	return sockAddr;
}

void Net::printSockAddrInfo(sockaddr_in& addr)
{
	char str[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &(addr.sin_addr), str, INET_ADDRSTRLEN);
	cout << str << ":" << ntohs(addr.sin_port);
}

bool Net::connectTo(SOCKET socket, sockaddr_in sockAddr)
{
	if (connect(socket, (sockaddr*)(&sockAddr), sizeof(sockAddr)) == SOCKET_ERROR)
	{
		cerr << "Connect - Error: " << WSAGetLastError() << endl;
		return false;
	}
	else
	{
		cout << "Connect: ";
		printSockAddrInfo(sockAddr);
		cout << endl;
		return true;
	}
}

void Net::bindListenSocket(SOCKET listenSocket, sockaddr_in sockAddr)
{
	if (::bind(listenSocket, (sockaddr*)(&sockAddr), sizeof(sockAddr)) == SOCKET_ERROR)
	{
		cerr << "Bind - Error: " << WSAGetLastError() << endl;
	}
	else
	{
		cout << "Bind: ";
		cout << listenSocket << " ";
		printSockAddrInfo(sockAddr);
		cout << endl;
	}
}

void Net::openListenSocket(SOCKET listenSocket)
{
	sockaddr_in sain = getPeerInfo(listenSocket);
	if (listen(listenSocket, 1) == SOCKET_ERROR)
	{
		cerr << "Listen - Error: " << WSAGetLastError() << endl;
	}
	else
	{
		cout << "Listen: ";
		cout << listenSocket << " ";
		printSockAddrInfo(sain);
		cout << endl;
	}
}

bool Net::acceptConnection(SOCKET listenSocket, SOCKET& remoteSocket, sockaddr_in& remoteAddr)
{
	int iRemoteAddrLen = sizeof(remoteAddr);

	remoteSocket = accept(listenSocket, (sockaddr*)&remoteAddr, &iRemoteAddrLen);

	if (remoteSocket == INVALID_SOCKET)
	{
		cerr << "Accept - Error: " << WSAGetLastError() << endl;
		cout << listenSocket << endl;
		return false;
	}
	else
	{
		cout << "Accept: ";
		printSockAddrInfo(remoteAddr);
		cout << endl;
		return true;
	}
}

int Net::recvData(SOCKET socket, Buffer<SerializedPacket>& pckBuffer)
{
	int bytesReceived;
	char buffer[PACKET_SIZE];
	
	bytesReceived = recv(socket, buffer, PACKET_SIZE, 0);

	if (bytesReceived == SOCKET_ERROR)
	{
		cerr << WSAGetLastError();
	}

	pckBuffer.push(SerializedPacket(buffer));
	
	cout << "recvData() ... exit ok\n";
	return bytesReceived;
}


void Net::sendData(SOCKET socket, Buffer<SerializedPacket>& pckBuffer)
{
	for (int i = 0; i < pckBuffer.size(); i++)
	{
		if (send(socket, pckBuffer.get(i).getData(), PACKET_SIZE, 0) == SOCKET_ERROR)
		{
			cerr << WSAGetLastError();
		}
		pckBuffer.invalidate(i);
	}
	cout << "sendData() ... exit ok\n";
}