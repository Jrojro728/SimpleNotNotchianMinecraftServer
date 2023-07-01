//Game.cpp: 游戏内阶段处理
#include "Game.h"

DWORD NormalProcess(LPVOID lpParam)
{
	int Result = 0;
	SOCKET ClientSocket = (SOCKET)lpParam;

	std::string VersionName;
	int ProtocolNum = 0;
	Result = HandShake(ClientSocket, VersionName, ProtocolNum);
	if (Result == 1)
		Result = Status(ClientSocket, VersionName, ProtocolNum);

	//关闭socket
	Result = shutdown(ClientSocket, SD_BOTH);
	if (Result == SOCKET_ERROR) {
		printf("shutdown failed: %d\n", WSAGetLastError());
		closesocket(ClientSocket);
		WSACleanup();
		return 1;
	}
	closesocket(ClientSocket);
	return Result;
}

int HandShake(SOCKET ClientSocket, std::string& VersionName, int& ProtocolNum)
{
	int offset = 0;
	int temp = 0;
	char* Data = new char[MAX_SIZEOF_PACKET];
	ResetOffset();
	ResetData();
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

	delete[] Data;
	return NextState;
}

int Status(SOCKET ClientSocket, const std::string& VersionName, int& ProtocolNum)
{
	int offset = 0;
	int temp = 0;
	char* Data = new char[MAX_SIZEOF_PACKET];
	ResetOffset();
	ResetData();
	RecvData();

	PacketBuilder PacketToSend;
	std::string StatusJson = GetStatusJson(VersionName, ProtocolNum);
	PacketToSend.Add(StatusJson);
	PacketToSend.GetPacket(temp);
	send(ClientSocket, (char*)PacketToSend.GetData(), (int) PacketToSend.GetSize(), 0);
	PacketToSend.Clear();

	ResetData();
	RecvData();
	send(ClientSocket, Data, MAX_SIZEOF_PACKET, 0);

	delete[] Data;
	return 0;
}