#pragma once

static const int PACKET_SIZE = 100;

class SerializedPacket
{
protected:
	char data[PACKET_SIZE];
public:
	SerializedPacket();
	SerializedPacket(const char*);
	const char* getData() { return data; }
	static const int getSize() { return PACKET_SIZE; }
	void printData();
};
