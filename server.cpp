#include "server.h"

using namespace std;

Server::Server()
{
	listenSocket = Net::openSocket();
	bindListenSocket(listenSocket, generateSocketAddr("127.0.0.1"));
	openListenSocket(listenSocket);

	clientThreads.reserve(MAX_CONNECTIONS_OPEN);

	// Spawn threads for client connections
	for (int i = 0; i < MAX_CONNECTIONS_OPEN; i++)
	{
		clientThreads.push_back(thread(&ThreadWrapper::run, ThreadWrapper(), &(clientConnectionPool[i])));
	}
}

Server::~Server()
{
	Net::closeSocket(listenSocket);
	for (int i = 0; i < MAX_CONNECTIONS_OPEN; i++)
	{
		if(clientThreads[i].joinable())
			clientThreads[i].join();
	}
}

void Server::run()
{
	int connectionId = findClosedConnection();
	if (Net::acceptConnection(listenSocket, remoteSocket, remoteAddr))
	{
		if (connectionId > -1)
		{
			cout << "Remote socket connection successful.\n";
			cout << "Starting connection " << connectionId << endl;
			clientConnectionPool[connectionId].setSocket(remoteSocket);
			clientConnectionPool[connectionId].setStatus(ClientConnection::OPEN);
		}
		else
			cout << "Max connections allowed.\n";
	}
	else
	{
		cout << "Server calls quit\n";
		optsHandle.quitProgram();
	}
}

int Server::findClosedConnection()
{
	for (int connectionId = 0; connectionId < MAX_CONNECTIONS_OPEN; connectionId++)
		if (clientConnectionPool[connectionId].getStatus() == ClientConnection::CLOSED)
		{
			return connectionId;
		}
	return -1; // not found
}

void Server::sendData()
{
	
}