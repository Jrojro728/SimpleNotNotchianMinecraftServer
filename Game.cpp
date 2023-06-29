//Game.cpp: 游戏内阶段处理
#include "Game.h"

int offset = 0;
int temp = 0;
char Data[MAX_SIZEOF_PACKET];
SOCKET ClientSocket;

int HandShake(std::string& VersionName, int& ProtocolNum)
{
	ResetOffset();
	RecvData();
	Packet HandShake(Data, offset);

	ProtocolNum = HandShake.GetVarInt(offset, temp);
	VersionName = GetVersion(ProtocolNum).VersionName;
	AddTempToOffset();
	std::string EntryServerIP = HandShake.GetString(offset, temp);
	AddTempToOffset();
	unsigned short Port = HandShake.GetAnyType<unsigned short>(offset, temp);
	AddTempToOffset();
	int NextState = HandShake.GetVarInt(offset, temp);
	AddTempToOffset();

	ResetData();
	return NextState;
}

int Status(const std::string& VersionName, int& ProtocolNum)
{
	ResetOffset();
	RecvData();

	PacketBuilder PacketToSend;
	std::string StatusJson = GetStatusJson(VersionName, ProtocolNum);
	PacketToSend.Add(StatusJson);
	PacketToSend.GetPacket(temp);
	send(ClientSocket, (char*)PacketToSend.GetData(), PacketToSend.GetSize(), 0);

	ResetData();
	RecvData();
	send(ClientSocket, Data, MAX_SIZEOF_PACKET, 0);

	ResetData();
	return 0;
}