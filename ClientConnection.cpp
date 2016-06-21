#include "ClientConnection.h"

using namespace std;

ClientConnection::ClientConnection() : status(CLOSED)
{}

void ClientConnection::recieveData()
{
	// recvData is blocking
	int bytesReceived = Net::recvData(clientSocket, recvBuf);

	if (bytesReceived == 0)
	{
		setStatus(CLOSED);
	}
}

void ClientConnection::sendData(Buffer<SerializedPacket>& sendBuf)
{
	Net::sendData(clientSocket, sendBuf);
}

void ClientConnection::setSocket(SOCKET socket)
{
	clientSocket = socket;
}

SOCKET ClientConnection::getSocket()
{
	return clientSocket;
}

void ClientConnection::setStatus(ConnectionStatus newStatus)
{
	status = newStatus;
}

ClientConnection::ConnectionStatus ClientConnection::getStatus()
{
	return status;
}

Buffer<SerializedPacket> ClientConnection::getRecvBuffer()
{
	return recvBuf;
}

////////////////////////////////////////////////////////////////

void ClientConnectionThread::wakeup()
{
	cvWait.notify_one();
}

void ClientConnectionThread::sleep()
{
	std::unique_lock<std::mutex> lck(mtx);
	cvWait.wait(lck);
}

void ClientConnectionThread::setStatus(ConnectionStatus newStatus)
{
	ClientConnection::setStatus(newStatus);
	if (newStatus == ClientConnection::OPEN)
		wakeup();
}

void ClientConnectionThread::run()
{
	std::unique_lock<std::mutex> lckWait;
	if (getStatus() == OPEN)
	{
		cout << "recieving data.\n";
		recieveData();
	}
	else if (getStatus() == CLOSED)
	{
		// needs to clear socket, recv last of data, etc.
		// https://msdn.microsoft.com/en-us/library/ms738547
		sleep();
	}
	cout << "client thread ended\n";
}
