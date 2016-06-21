#include "packet.h"
#include <iostream>

using namespace std;

SerializedPacket Packet::serializePacket()
{
	char data[PACKET_SIZE];
	for (int i = 0; i < PACKET_SIZE; i++)
		data[i] = 0;
	serialize(data);
	return SerializedPacket(data);
}

void Packet::unserializePacket(SerializedPacket pck)
{
	unserialize(pck.getData());
}

void Packet::serialize(char* outStr)
{
	outStr[TYPE] = packetType;
	outStr[ID] = packetId;
}

void PacketHeader::serialize(char* outStr)
{
	Packet::serialize(outStr);
	outStr[NUMOFPACKETS] = numOfPackets;
	int usernameLength = username.length();
	int length = usernameLength < USERNAME_SIZE ? usernameLength : USERNAME_SIZE;
	for (int i = 0; i < length; i++)
	{
		outStr[i + USERNAME] = username[i];
	}
}

void PacketData::serialize(char* outStr)
{
	Packet::serialize(outStr);
	outStr[NUMBER] = packetNum;
	int msgLength = msg.length();
	int length = msgLength < MSG_SIZE ? msgLength : MSG_SIZE;
	for (int i = 0; i < length; i++)
	{
		outStr[i + MSG] = msg[i];
	}
}

void Packet::unserialize(const char* data)
{
	packetType = (PacketType)data[TYPE];
	packetId = data[ID];
}

void PacketHeader::unserialize(const char* data)
{
	Packet::unserialize(data);
	numOfPackets = data[NUMOFPACKETS];
	for (int i = USERNAME; i < USERNAME_SIZE; i++)
	{
		if (data[i] != 0)
			username.push_back(data[i]);
	}
}

void PacketData::unserialize(const char* data)
{
	Packet::unserialize(data);
	packetNum = data[NUMBER];
	for (int i = MSG; i < MSG_SIZE + MSG; i++)
	{
		if (data[i] != 0)
			msg.push_back(data[i]);
	}
}