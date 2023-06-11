// SimpleNotNotchianMinecraftServer.cpp : main entry of program

#include <iostream>
#include "WinSock2Usage.h"
#include "Packet.h"
#include "Utils.h"
#include "PacketBuilder.h"

int offset = 0, temp = 0;
char Data[MAX_SIZEOF_PACKET];
SOCKET ClientSocket;

#define AddTempToOffset() offset += temp
#define RecvData() recv(ClientSocket, Data, MAX_SIZEOF_PACKET, 0)

int HandShake(std::string &VersionName, int &ProtocolNum);
int Status(const std::string& VersionName, int& ProtocolNum);

int main()
{
	PacketBuilder Test;
	unsigned short mmmm = 25565;
	Test.Add<unsigned short>(&mmmm);

	int Result = 0;
	InitWinsock2(ClientSocket);
	memset(Data, 0, sizeof(Data));
	
	std::string VersionName;
	int ProtocolNum = 0; 
	Result = HandShake(VersionName, ProtocolNum);
	if (Result == 1)
		Status(VersionName, ProtocolNum);

	Result = shutdown(ClientSocket, SD_SEND);
	if (Result == SOCKET_ERROR) {
		printf("shutdown failed: %d\n", WSAGetLastError());
		closesocket(ClientSocket);
		WSACleanup();
		return 1;
	}
	closesocket(ClientSocket);
	WSACleanup();
	return 0;
}

int HandShake(std::string& VersionName, int& ProtocolNum)
{
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

	return NextState;
}

int Status(const std::string& VersionName, int& ProtocolNum)
{
	RecvData();
	Packet Status(Data, offset);

	std::string StatusJson = GetStatusJson(VersionName, ProtocolNum);

	return 0;
}
