// SimpleNotNotchianMinecraftServer.cpp : main entry of program

#include <iostream>
#include "WinSock2Usage.h"
#include "Packet.h"
#include "Utils.h"

int offset = 0, temp = 0;
char Data[MAX_SIZEOF_PACKET];

#define AddTempToOffset() offset += temp

void HandShake(char* Data);

int main()
{
	SOCKET ClientSocket;
	InitWinsock2(ClientSocket);
	memset(Data, 0, sizeof(Data));
	
	recv(ClientSocket, Data, MAX_SIZEOF_PACKET, 0);
	HandShake(Data);

	return 0;
}

void HandShake(char* Data)
{
	Packet HandShake(Data, offset);

	int ProtocolNum = HandShake.GetVarInt(offset, temp);
	GetVersion(ProtocolNum);
	/*AddTempToOffset();
	std::string EntryServerIP = HandShake.GetString(offset, temp);
	AddTempToOffset();
	unsigned short Port = HandShake.GetAnyType<unsigned short>(offset, temp);
	AddTempToOffset();
	int NextState = HandShake.GetVarInt(offset, temp);
	AddTempToOffset();*/
}