#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "packet.h"
#include "Buffer.h"
#include "SerializedPacket.h"


typedef int PacketId;

class PacketHandler
{
	typedef std::vector<SerializedPacket> SerialPckVec;
	typedef std::vector<SerialPckVec> SerialPckVec2;

	void packHead(SerialPckVec&, PacketId, int numOfPackets, std::string username);
	void packData(SerialPckVec&, PacketId, int numOfPackets, std::string data);
	void packBuffer(Buffer<SerializedPacket>&, SerialPckVec&);

	void unpackHead(std::string& username, PacketHeader packet);
	void unpackData(SerialPckVec&, std::string& data, PacketId);
	void unpackBuffer(Buffer<SerializedPacket>&, SerialPckVec2&);

	void removePackets(SerialPckVec2&, PacketId);
	bool checkAllPacketsHaveArrived(PacketHeader, SerialPckVec&);
	PacketId generatePacketId();
	int numOfPackets(std::string data);

public:
	// -!- serialize and unserialize when pushing to the lists 
	// -?- maybe 4 lists - 2 for headers and 2 for data
	void pack(Buffer<SerializedPacket>&, std::string username, std::string data);
	void unpack(Buffer<SerializedPacket>&, std::string& username, std::string& data);
};

