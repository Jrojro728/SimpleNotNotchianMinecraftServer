﻿//Game.cpp: 游戏内阶段处理
#include "pch.h"
#include "Game.h"
#include <list>
#include "DataEnum.h"

binlog::Session session;
binlog::SessionWriter worker(session);

int BiggestPlayerNumber = 0;
std::vector<Player> PlayerList;

DWORD NormalProcess(LPVOID lpParam)
{
	int Result = 0;
	SOCKET ClientSocket = (SOCKET)lpParam;

	std::string VersionName;
	int ProtocolNum = 0;
	int ThreadPlayer = 0;
	Result = HandShake(ClientSocket, VersionName, ProtocolNum);
	if (Result == 1)
		Result = Status(ClientSocket, VersionName, ProtocolNum);
	else if (Result == 2)
	{
		Result = Login(ClientSocket, ThreadPlayer);
		Result = Play(ClientSocket, ThreadPlayer);
	}
	else
		throw "Error nextstate";

	//关闭socket
	Result = shutdown(ClientSocket, SD_BOTH);
	if (Result == SOCKET_ERROR) {
		printf("shutdown failed: %d\n", WSAGetLastError());
		closesocket(ClientSocket);
		WSACleanup();
		return 1;
	}
	closesocket(ClientSocket);
	return Result;
}

int HandShake(SOCKET ClientSocket, std::string& VersionName, int& ProtocolNum)
{
	int offset = 0;
	int temp = 0;
	char* Data = new char[THREE_BYTE_PACKET];
	
	BINLOG_INFO_WC_CONSUME(worker, handshake, "进入握手阶段");
	ResetOffset();
	ResetData(THREE_BYTE_PACKET);
	RecvData(THREE_BYTE_PACKET);

	if (Data[0] == 0)
	{
		BINLOG_CRITICAL_C_CONSUME(Handshake, "无效的数据: NULL");
		return -1;
	}

	Packet HandShake(Data, offset);

	ProtocolNum = HandShake.GetVarInt(offset, temp);
	VersionName = GetVersion(ProtocolNum);
	BINLOG_INFO_C_CONSUME(handshake, "客户端游戏版本: {}", VersionName);
	AddTempToOffset();
	std::string EntryServerIP = HandShake.GetString(offset, temp);
	BINLOG_INFO_C_CONSUME(handshake, "客户端连接的IP: {}", EntryServerIP);
	AddTempToOffset();
	unsigned short Port = HandShake.GetAnyType<unsigned short>(offset, temp);
	BINLOG_INFO_C_CONSUME(handshake, "客户端使用的端口: {}", Port);
	AddTempToOffset();
	int NextState = HandShake.GetVarInt(offset, temp);
	AddTempToOffset();
	BINLOG_INFO_C_CONSUME(handshake, "握手完成");
	delete[] Data;
	return NextState;
}

int Status(SOCKET ClientSocket, const std::string& VersionName, int& ProtocolNum)
{
	int temp = 0;
	char* Data = new char[THREE_BYTE_PACKET];
	BINLOG_INFO_C_CONSUME(status, "进入Status阶段");
	ResetData(THREE_BYTE_PACKET);
	RecvData(THREE_BYTE_PACKET);
	
	if (Data[0] == 0)
	{
		BINLOG_CRITICAL_C_CONSUME(status, "无效的数据: NULL");
		return -1;
	}

	PacketBuilder PacketToSend;
	std::string StatusJson = GetStatusJson(VersionName, ProtocolNum);
	PacketToSend.Add(StatusJson);
	PacketToSend.GetPacket(temp);
	send(ClientSocket, PacketToSend, PacketToSend, 0);
	PacketToSend.Clear();

	ResetData(THREE_BYTE_PACKET);
	RecvData(THREE_BYTE_PACKET);
	send(ClientSocket, Data, THREE_BYTE_PACKET, 0);

	BINLOG_INFO_C_CONSUME(status, "Status阶段完成");
	delete[] Data;
	return 0;
}

int Login(SOCKET ClientSocket, int &ThreadPlayer)
{
	int offset = 0, temp = 0;
	char* Data = new char[THREE_BYTE_PACKET];
	BINLOG_INFO_C_CONSUME(login, "进入登录阶段");
	ResetData(THREE_BYTE_PACKET);
	RecvData(THREE_BYTE_PACKET);

	Packet LoginStart(Data, offset);
	std::string PlayerName = LoginStart.GetString(offset, temp);
	BINLOG_INFO_C_CONSUME(login, "玩家名: {}", PlayerName);
	ResetOffset();

	//TODO: 增加封禁系统
	/*PacketBuilder Disconnect(0x00);
	Disconnect.Add(std::string(StringToUTF8("{\"text\": \"你已被封禁\"}")));
	send(ClientSocket, (char*)Disconnect.GetData(), THREE_BYTE_PACKET, 0);*/

	//TODO:正版验证
	std::string UUID = GetRandomUUID();
	BINLOG_INFO_C_CONSUME(login, "玩家UUID: {}", UUID);
	PacketBuilder LoginSuccess(0x02);
	LoginSuccess.Add(UUID);
	LoginSuccess.Add(PlayerName);
	send(ClientSocket, LoginSuccess, LoginSuccess, 0);
	LoginSuccess.Clear();

	PlayerList.push_back(Player(PlayerName, UUID));
	BINLOG_INFO_C_CONSUME(login, "编号为{}的玩家数据: [{}, {}]", BiggestPlayerNumber, PlayerList.at(BiggestPlayerNumber).Name, PlayerList.at(BiggestPlayerNumber).UUID);
	ThreadPlayer = BiggestPlayerNumber;
	BiggestPlayerNumber++;

	BINLOG_INFO_C_CONSUME(login, "登录完成");
	delete[] Data;
	return 0;
}

int Play(SOCKET ClientSocket, int& ThreadPlayer)
{
	int offset = 0, temp = 0;
	char* Data = new char[THREE_BYTE_PACKET];
	BINLOG_INFO_C_CONSUME(play, "进入游玩阶段");
	ResetData(THREE_BYTE_PACKET);

	PacketBuilder JoinGame(0x23);
	JoinGame.Add<int>(1); //EID
	JoinGame.Add<uint8_t>(Creative); //模式
	JoinGame.Add<int>(0); //维度
	JoinGame.Add<uint8_t>(Normal); //难度
	JoinGame.Add<uint8_t>((uint8_t)2); //最大玩家数
	JoinGame.Add(std::string("default"));
	JoinGame.Add<bool>(false);
	send(ClientSocket, JoinGame, JoinGame, 0);

	PacketBuilder ServerDifficulty(0x0D);
	ServerDifficulty.Add<uint8_t>(Normal);
	send(ClientSocket, ServerDifficulty, ServerDifficulty, 0);
	
	BINLOG_INFO_C_CONSUME(play, "玩家登出");
	delete[] Data;
	return 0;
}
