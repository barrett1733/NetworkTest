#include "client.h"

using namespace std;

bool Client::connectTo(string ipAddr)
{
	sockaddr_in clientAddr = Net::generateSocketAddr(ipAddr);
	return Net::connectTo(clientSocket, clientAddr);
}

void Client::sendData(string username, string data)
{
	Buffer<SerializedPacket> buf;
	pack(buf, username, data);
	Net::sendData(clientSocket, buf);
}

