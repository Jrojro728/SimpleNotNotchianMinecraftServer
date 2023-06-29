// SimpleNotNotchianMinecraftServer.cpp: 程序的入口点和协议阶段的处理
#include <iostream>
#include "Game.h"

int main()
{
	int Result = 0;
	SOCKET ListenSocket;

	Result = InitWinsock2(ListenSocket);
	if (Result != 0)
		return Result;
	while (true)
	{
		SOCKET ClientSocket = INVALID_SOCKET;
		Result = AcceptConnect(ListenSocket, ClientSocket);
		if (Result != 0)
			return Result;

		CreateThread(NULL, 0, NormalProcess, (LPVOID)ClientSocket, 0, NULL);
	}
	
	WSACleanup();
	return Result;
}
