// SimpleNotNotchianMinecraftServer.cpp: 程序的入口点和初始化处理
#include "pch.h"
#include <iostream>
#include "Game.h"

int main()
{
	PacketBuilder test(0x21);

	int Result = 0;
	SOCKET ListenSocket;

	Result = InitWinsock2(ListenSocket);
	if (Result != 0) 
	{
		BINLOG_CRITICAL_C_CONSUME(init, "初始化Winsock2失败, 返回: {}", Result);
		return Result;
	}
																		
	BINLOG_INFO_C_CONSUME(init, "初始化Winsock2成功");

	while (true)
	{
		SOCKET ClientSocket = INVALID_SOCKET;
		Result = AcceptConnect(ListenSocket, ClientSocket);
		BINLOG_INFO_C_CONSUME(connect, "玩家尝试连接");
		if (Result != 0)
		{
			BINLOG_CRITICAL_C_CONSUME(connect, "玩家连接失败, 返回: {}", Result);
			return Result;
		}
		BINLOG_INFO_C_CONSUME(connect, "玩家连接成功");

		CreateThread(NULL, 0, NormalProcess, (LPVOID)ClientSocket, 0, NULL);
	}
	
	WSACleanup();
	return Result;
}
