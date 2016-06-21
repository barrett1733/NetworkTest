#include "SerializedPacket.h"
#include <iostream>

using namespace std;

SerializedPacket::SerializedPacket()
{
	for (int i = 0; i < PACKET_SIZE; i++)
		data[i] = 0;
}

// -!- Warning: Assumes the input char* is the same size as PACKET_SIZE
SerializedPacket::SerializedPacket(const char* _data) : SerializedPacket()
{
	for (int i = 0; i < PACKET_SIZE; i++)
		data[i] = _data[i];
}

void SerializedPacket::printData()
{
	cout << "Data: ";
	for (int i = 0; i < PACKET_SIZE; i++)
		std::cout << data[i] << "|" << (int)data[i] << " ";
	std::cout << std::endl;
}
