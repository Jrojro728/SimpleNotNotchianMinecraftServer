// SimpleNotNotchianMinecraftServer.cpp: 程序的入口点和协议阶段的处理

#include <iostream>
#include "Game.h"

extern int offset;
extern int temp;
extern char Data[MAX_SIZEOF_PACKET];
extern SOCKET ClientSocket;

int main()
{
	int Result = 0;
	SOCKET ListenSocket;

	Result = InitWinsock2(ListenSocket);
	if (Result != 0)
		return Result;
	Result = AcceptConnect(ListenSocket, ClientSocket);
	if (Result != 0)
		return Result;
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
