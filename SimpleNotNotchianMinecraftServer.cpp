// SimpleNotNotchianMinecraftServer.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
// TODO:分开代码到不同的文件

#include <iostream>
#include "WinSock2Usage.h"

int main()
{ 
    SOCKET ClientSocket;
    InitWinsock2(ClientSocket);

    char Data[512] = { 0 };
    memset(Data, 0, sizeof(Data));

    recv(ClientSocket, Data, 512, 0);
}