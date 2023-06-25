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
#define ResetOffset() offset = 0
#define ResetData() memset(Data, 0, MAX_SIZEOF_PACKET)
#define RecvData() recv(ClientSocket, Data, MAX_SIZEOF_PACKET, 0)

int HandShake(std::string &VersionName, int &ProtocolNum);
int Status(const std::string& VersionName, int& ProtocolNum);

int main()
{
	int Result = 0;
	InitWinsock2(ClientSocket);
	ResetData();
	
	std::string VersionName;
	int ProtocolNum = 0; 
	Result = HandShake(VersionName, ProtocolNum);
	if (Result == 1)
		Result = Status(VersionName, ProtocolNum);

	//关闭socket
	Result = shutdown(ClientSocket, SD_BOTH);
	if (Result == SOCKET_ERROR) {
		printf("shutdown failed: %d\n", WSAGetLastError());
		closesocket(ClientSocket);
		WSACleanup();
		return 1;
	}
	closesocket(ClientSocket);
	WSACleanup();
	return Result;
}

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
	long long RandomDataFromClient = 0;
	send(ClientSocket, Data, MAX_SIZEOF_PACKET, 0);

	ResetData();
	return 0;
}
