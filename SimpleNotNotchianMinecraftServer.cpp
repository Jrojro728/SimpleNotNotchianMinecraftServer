﻿// SimpleNotNotchianMinecraftServer.cpp: 程序的入口点和协议阶段的处理
#include <iostream>
#include "Game.h"

int main()
{
	int Result = 0, CumulativePlayerConnect = 0;
	SOCKET ListenSocket;

	Result = InitWinsock2(ListenSocket);
	if (Result != 0) 
	{
		BINLOG_CRITICAL_CONSUME("初始化Winsock2失败, 返回: {}", Result);
		return Result;
	}

	BINLOG_INFO_CONSUME("初始化Winsock2成功");

	while (true)
	{
		SOCKET ClientSocket = INVALID_SOCKET;
		Result = AcceptConnect(ListenSocket, ClientSocket);
		CumulativePlayerConnect++;
		BINLOG_INFO_CONSUME("第{}个玩家尝试连接", CumulativePlayerConnect);
		if (Result != 0)
		{
			BINLOG_CRITICAL_CONSUME("玩家连接失败, 返回: {}", Result);
			return Result;
		}
		BINLOG_INFO_CONSUME("第{}个玩家连接成功", CumulativePlayerConnect);

		CreateThread(NULL, 0, NormalProcess, (LPVOID)ClientSocket, 0, NULL);
	}
	
	WSACleanup();
	return Result;
}
