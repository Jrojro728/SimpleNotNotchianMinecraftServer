// SimpleNotNotchianMinecraftServer.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
// TODO:分开代码到不同的文件

#include <iostream>
#include "WinSock2Usage.h"
#include "Packet.h"

char Data[MAX_SIZEOF_PACKET];

int main()
{
	SOCKET ClientSocket;
	InitWinsock2(ClientSocket);
	memset(Data, 0, sizeof(Data));

	int offset = 0, temp = 0;
	recv(ClientSocket, Data, MAX_SIZEOF_PACKET, 0);
	Packet HandShake(Data, offset);
	HandShake.GetVarInt(offset, offset);
	HandShake.GetString(offset + 2, offset);

	return 0;
}