#include "PacketHandler.h"
#include <bitset>

using namespace std;

// Called once per data packing
PacketId PacketHandler::generatePacketId()
{
	static int genPacketId = 0;
	return genPacketId++;
}

int PacketHandler::numOfPackets(std::string data)
{
	int dataSize = data.length();
	int dataPacketSize = PacketData::getDataSize();
	int numDataPackets = (dataSize / dataPacketSize) + (dataSize % dataPacketSize != 0 ? 1 : 0);
	return numDataPackets;
}

void PacketHandler::removePackets(SerialPckVec2& pckSortVec, PacketId pckId)
{
	for (int type = 0; type < Packet::PacketType::AMT; type++)
	{
		for (SerialPckVec::iterator iter = pckSortVec[type].begin(); iter != pckSortVec[type].end();)
		{
			Packet temp(*iter);
			if (temp.packetId == pckId)
				iter = pckSortVec[type].erase(iter);
			else
				++iter;
		}
	}
}

void PacketHandler::pack(Buffer<SerializedPacket>& serialPckBuffer, std::string username, std::string data)
{
	PacketId packetId = generatePacketId();
	int packetAmt = numOfPackets(data);

	SerialPckVec buffer;

	packHead(buffer, packetId, packetAmt, username);
	packData(buffer, packetId, packetAmt, data);

	packBuffer(serialPckBuffer, buffer);
}

void PacketHandler::packHead(SerialPckVec& buf, PacketId packetId, int numDataPackets, std::string username)
{
	PacketHeader newHead;

	newHead.packetType = Packet::PacketType::HEADER;
	newHead.packetId = packetId;

	newHead.username = username;
	newHead.numOfPackets = numDataPackets + 1;
	buf.push_back(newHead.serializePacket());
}

void PacketHandler::packData(SerialPckVec& buf, PacketId packetId, int numDataPackets, std::string data)
{
	for (int i = 0; i < numDataPackets; i++)
	{
		int dataSize = PacketData::getDataSize() < data.length() ? PacketData::getDataSize() : data.length();
		PacketData newData;

		newData.packetType = Packet::PacketType::DATA;
		newData.packetId = packetId;

		newData.packetNum = i;
		newData.msg = data.substr(i * dataSize, (i + 1) * dataSize);

		buf.push_back(newData.serializePacket());
	}
}

void PacketHandler::packBuffer(Buffer<SerializedPacket>& serialPckBuffer, SerialPckVec& buf)
{
	while (!buf.empty())
	{
		SerializedPacket* pck = &buf.front();
		if (!serialPckBuffer.full())
		{
			serialPckBuffer.push(*pck);
			buf.erase(buf.begin());
		}
	}
}

bool PacketHandler::checkAllPacketsHaveArrived(PacketHeader pck, SerialPckVec& pckVec)
{
	int packetCounter = 0;
	for (int i = 0; i < pckVec.size(); i++)
	{
		Packet temp(pckVec[i]);
		if (temp.packetId == pck.packetId)
		{
			packetCounter++;
		}
	}
	if (packetCounter == pck.numOfPackets - 1)
		return true;
	else return false;
}

void PacketHandler::unpack(Buffer<SerializedPacket>& recvBuf, std::string& username, std::string& data)
{
	SerialPckVec2 sortingVec;
	unpackBuffer(recvBuf, sortingVec);
	if (!sortingVec[Packet::PacketType::HEADER].empty())
	{
		for (int i = 0; i < sortingVec[Packet::PacketType::HEADER].size(); i++)
		{
			PacketHeader curHeader(sortingVec[Packet::PacketType::HEADER][i]);

			if (checkAllPacketsHaveArrived(curHeader, sortingVec[Packet::PacketType::DATA]))
			{
				unpackHead(username, curHeader);
				unpackData(sortingVec[Packet::PacketType::DATA], data, curHeader.packetId);
				removePackets(sortingVec, curHeader.packetId);
			}
		}
	}
}

void PacketHandler::unpackBuffer(Buffer<SerializedPacket>& recvBuf, SerialPckVec2& sortingVec)
{
	Packet buf;
	sortingVec.resize(Packet::PacketType::AMT);
	for (int i = Packet::PacketType::BAD + 1; i < Packet::PacketType::AMT; i++)
	{
		sortingVec[i].reserve(recvBuf.size());
	}

	for (int i = 0; i < recvBuf.size(); i++)
	{
		buf.unserializePacket(recvBuf.get(i));
		sortingVec[buf.packetType].push_back(recvBuf.get(i));
	}
}

void PacketHandler::unpackHead(std::string& username, PacketHeader packet)
{
	//cout << "Unpacking header - id:" << packet.packetId << endl;
	username = packet.username;
}

void PacketHandler::unpackData(SerialPckVec& pckVec, std::string& data, PacketId pckId)
{
	for (int i = 0; i < pckVec.size(); i++)
	{
		PacketData pckData(pckVec[i]);
		if (pckData.packetId == pckId)
		{
			//cout << "Unpacking data - id:" << pckData.packetId << "\n - #:" << pckData.packetNum << endl;
			data.append(pckData.msg);
		}
	}
}