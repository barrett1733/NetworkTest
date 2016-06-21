#pragma once

#include <string>
#include "SerializedPacket.h"

/*
--------- Info
0	1 : packet type
1	4 : packet id

--------- Header
0	  : Info
5	4 : number of packets
9	25 : username

--------- Data
0	  : Info
5	4 : packet number
9	100 : packet message
*/

class Packet
{
	static const int TYPE = 0;
	static const int TYPE_SIZE = 1;
	static const int ID = TYPE + TYPE_SIZE;
	static const int ID_SIZE = 2;

protected:
	static const int SIZE = TYPE_SIZE + ID_SIZE;
	virtual void serialize(char*);
	virtual void unserialize(const char*);
public:
	enum PacketType
	{
		BAD = 0, HEADER, DATA, AMT
	};
	PacketType packetType;
	unsigned int packetId;

	Packet(){}
	Packet(SerializedPacket pck) { unserializePacket(pck); }
	SerializedPacket serializePacket();
	void unserializePacket(SerializedPacket);
};

class PacketHeader : public Packet
{

	static const int SIZE = PACKET_SIZE;
	static const int NUMOFPACKETS = Packet::SIZE;
	static const int NUMOFPACKETS_SIZE = 2;
	static const int USERNAME = NUMOFPACKETS + NUMOFPACKETS_SIZE;
	static const int USERNAME_SIZE = 25;
protected:
	void serialize(char*);
	void unserialize(const char*);
public:
	std::string username;
	unsigned int numOfPackets;

	PacketHeader(){}
	PacketHeader(SerializedPacket pck) { unserializePacket(pck); }

	static int getUsernameSize(){ return USERNAME_SIZE; }
};

class PacketData : public Packet
{
	void serialize(char*);
	void unserialize(const char*);

	static const int SIZE = PACKET_SIZE;
	static const int NUMBER = Packet::SIZE;
	static const int NUMBER_SIZE = 2;
	static const int MSG = NUMBER + NUMBER_SIZE;
	static const int MSG_SIZE = SIZE - MSG;

public:
	unsigned int packetNum;
	std::string msg;

	PacketData(){}
	PacketData(SerializedPacket pck) { unserializePacket(pck); }
	static int getDataSize(){ return MSG_SIZE; }

};