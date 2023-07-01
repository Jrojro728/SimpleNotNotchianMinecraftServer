﻿//WinSock2Usage.cpp: Windows的网络api功能
#include "WinSock2Usage.h"

#pragma comment(lib, "Ws2_32.lib")
#define DEFAULT_PORT "25565"

int InitWinsock2(SOCKET& ListenSocket)
{
	WSADATA WsaData;
	int iResult;

	iResult = WSAStartup(MAKEWORD(2, 2), &WsaData);
	if (iResult != 0) {
		printf("运行时出现错误: %d\n", iResult);
		return 1;
	}

	struct addrinfo* Result = NULL, * Ptr = NULL, Hints;

	ZeroMemory(&Hints, sizeof(Hints));
	Hints.ai_family = AF_INET;
	Hints.ai_socktype = SOCK_STREAM;
	Hints.ai_protocol = IPPROTO_TCP;
	Hints.ai_flags = AI_PASSIVE;

	iResult = getaddrinfo(NULL, DEFAULT_PORT, &Hints, &Result);
	if (iResult != 0) {
		printf("运行时出现错误: %d\n", iResult);
		WSACleanup();
		return 1;
	}

	ListenSocket = socket(Result->ai_family, Result->ai_socktype, Result->ai_protocol);
	if (ListenSocket == INVALID_SOCKET) {
		printf("执行socket()时错误: %ld\n", WSAGetLastError());
		freeaddrinfo(Result);
		WSACleanup();
		return 1;
	}

	iResult = bind(ListenSocket, Result->ai_addr, (int)Result->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		printf("绑定错误: %d\n", WSAGetLastError());
		freeaddrinfo(Result);
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}
	freeaddrinfo(Result);

	if (listen(ListenSocket, SOMAXCONN) == SOCKET_ERROR) {
		printf("监听错误: %ld\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

	return 0;
}

int AcceptConnect(SOCKET ListenSocket, SOCKET& ClientSocket)
{
	ClientSocket = INVALID_SOCKET;
	ClientSocket = accept(ListenSocket, NULL, NULL);
	if (ClientSocket == INVALID_SOCKET) {
		printf("接受连接错误: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}
	
	return 0;
}
