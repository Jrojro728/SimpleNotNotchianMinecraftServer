// SimpleNotNotchianMinecraftServer.cpp: 程序的入口点和协议阶段的处理
#include <iostream>
#include <conio.h>
#include "Game.h"

DWORD CheckClientConnect(LPVOID);

int main()
{
	int Result = 0;
	SOCKET ListenSocket;
	HANDLE ConnectHandle;

	Result = InitWinsock2(ListenSocket);
	if (Result != 0)
		return Result;
	ConnectHandle = CreateThread(NULL, 0, CheckClientConnect, (LPVOID)ListenSocket, 0, NULL);

	while (true)
	{
		if (_kbhit())//非阻塞获取用户输入
		{
			std::string sInput;
			char cTake = _getche();//获取输入字符,并回显		
			if (cTake == 'q' || cTake == 'Q')
			{
				CloseHandle(ConnectHandle);
				break;
			}
			sInput = sInput + cTake;
		}
	}
	std::cout << "\n退出中...\n";
	
	WSACleanup();
	return Result;
}

DWORD CheckClientConnect(LPVOID ListenSocket)
{
	while (true)
	{
		int Result = 0;
		SOCKET ClientSocket = INVALID_SOCKET;
		Result = AcceptConnect((SOCKET)ListenSocket, ClientSocket);
		if (Result != 0)
			return Result;

		CreateThread(NULL, 0, NormalProcess, (LPVOID)ClientSocket, 0, NULL);
	}
}
