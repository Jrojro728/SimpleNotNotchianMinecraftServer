//Game.cpp: 游戏内阶段处理
#include "Game.h"

binlog::Session session;
binlog::SessionWriter worker(session);

DWORD NormalProcess(LPVOID lpParam)
{
	int Result = 0;
	SOCKET ClientSocket = (SOCKET)lpParam;

	std::string VersionName;
	int ProtocolNum = 0;
	Result = HandShake(ClientSocket, VersionName, ProtocolNum);
	if (Result == 1)
		Result = Status(ClientSocket, VersionName, ProtocolNum);

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
	char* Data = new char[TWO_BYTE_PACKET];
	
	BINLOG_INFO_WC_CONSUME(worker, Handshake, "进入握手阶段");
	ResetOffset();
	ResetData(TWO_BYTE_PACKET);
	RecvData(TWO_BYTE_PACKET);

	if (Data[0] == 0)
	{
		BINLOG_CRITICAL_C_CONSUME(Handshake, "无效的数据: NULL");
		return -1;
	}

	Packet HandShake(Data, offset);

	ProtocolNum = HandShake.GetVarInt(offset, temp);
	VersionName = GetVersion(ProtocolNum);
	BINLOG_INFO_C_CONSUME(Handshake, "客户端游戏版本: {}", VersionName);
	AddTempToOffset();
	std::string EntryServerIP = HandShake.GetString(offset, temp);
	BINLOG_INFO_C_CONSUME(Handshake, "客户端连接的IP: {}", EntryServerIP);
	AddTempToOffset();
	unsigned short Port = HandShake.GetAnyType<unsigned short>(offset, temp);
	BINLOG_INFO_C_CONSUME(Handshake, "客户端使用的端口: {}", Port);
	AddTempToOffset();
	int NextState = HandShake.GetVarInt(offset, temp);
	AddTempToOffset();

	BINLOG_INFO_C_CONSUME(Handshake, "握手阶段完成");
	delete[] Data;
	return NextState;
}

int Status(SOCKET ClientSocket, const std::string& VersionName, int& ProtocolNum)
{
	int temp = 0;
	char* Data = new char[TWO_BYTE_PACKET];
	BINLOG_INFO_C_CONSUME(Status, "进入Status阶段");
	ResetData(TWO_BYTE_PACKET);
	RecvData(TWO_BYTE_PACKET);
	
	if (Data[0] == 0)
	{
		BINLOG_CRITICAL_C_CONSUME(Status, "无效的数据: NULL");
		return -1;
	}

	PacketBuilder PacketToSend;
	std::string StatusJson = GetStatusJson(VersionName, ProtocolNum);
	PacketToSend.Add(StatusJson);
	PacketToSend.GetPacket(temp);
	send(ClientSocket, (char*)PacketToSend.GetData(), (int) PacketToSend.GetSize(), 0);
	PacketToSend.Clear();

	ResetData(TWO_BYTE_PACKET);
	RecvData(TWO_BYTE_PACKET);
	send(ClientSocket, Data, TWO_BYTE_PACKET, 0);

	BINLOG_INFO_C_CONSUME(Status, "Status阶段完成");
	delete[] Data;
	return 0;
}