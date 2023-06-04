// SimpleNotNotchianMinecraftServer.cpp : main entry of program

#include <iostream>
#include "WinSock2Usage.h"
#include "Packet.h"
#include "Utils.h"

int offset = 0, temp = 0;
char Data[MAX_SIZEOF_PACKET];
SOCKET ClientSocket;

#define AddTempToOffset() offset += temp

int HandShake(char* Data, std::string &VersionName, int &ProtocolNum);
int Status(const std::string& VersionName, int& ProtocolNum);

int main()
{
	int Result = 0;
	InitWinsock2(ClientSocket);
	memset(Data, 0, sizeof(Data));
	
	recv(ClientSocket, Data, MAX_SIZEOF_PACKET, 0);
	std::string VersionName;
	int ProtocolNum = 0; 
	Result = HandShake(Data, VersionName, ProtocolNum);
	if (Result == 1)
		Status(VersionName, ProtocolNum);

	return 0;
}

int HandShake(char* Data, std::string& VersionName, int& ProtocolNum)
{
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
	GetStatusJson(VersionName, ProtocolNum);

	return 0;
}
