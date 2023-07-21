//Game.cpp: 游戏内阶段处理
#include "Game.h"

std::map<int, Player> OnlinePlayer;
std::map<int, bool> EmptyPlayerSlot;
int MaxPlayerIndex = 1;

DWORD NormalProcess(LPVOID lpParam)
{
	int Result = 0, ThisThreadPlayer = 0;
	SOCKET ClientSocket = (SOCKET)lpParam;

	std::string VersionName;
	int ProtocolNum = 0;
	Result = HandShake(ClientSocket, VersionName, ProtocolNum);
	//Nextstate 1为请求状态, 2为请求登录
	if (Result == 1)
		Result = Status(ClientSocket, VersionName, ProtocolNum);
	else if (Result == 2)
		Result = Login(ClientSocket, ThisThreadPlayer);

	//关闭socket
	Result = shutdown(ClientSocket, SD_BOTH);
	if (Result == SOCKET_ERROR) {
		printf("shutdown failed: %d\n", WSAGetLastError());
		closesocket(ClientSocket);
		WSACleanup();
		return 1;
	}
	closesocket(ClientSocket);
	EmptyPlayerSlot[ThisThreadPlayer] = true;
	return Result;
}

int HandShake(SOCKET ClientSocket, std::string& VersionName, int& ProtocolNum)
{
	int offset = 0;
	int temp = 0;
	char* Data = new char[MAX_SIZEOF_PACKET];
	ResetData();
	RecvData();
	Packet HandShake(Data, offset);

	ProtocolNum = HandShake.GetVarInt(offset, temp);
	VersionName = GetVersion(ProtocolNum).VersionName;
	AddTempToOffset();
	std::string EntryServerIP = HandShake.GetString(offset, temp);
	AddTempToOffset();
	unsigned short Port = HandShake.GetAnyType<unsigned short>(offset, temp);
	AddTempToOffset();
	int NextState = HandShake.GetVarInt(offset, temp);
	AddTempToOffset();

	delete[] Data;
	return NextState;
}

int Status(SOCKET ClientSocket, const std::string& VersionName, int& ProtocolNum)
{
	int offset = 0;
	int temp = 0;
	char* Data = new char[MAX_SIZEOF_PACKET];
	ResetData();
	RecvData();

	PacketBuilder Response;
	std::string StatusJson = GetStatusJson(VersionName, ProtocolNum);
	Response.Add(StatusJson);
	send(ClientSocket, Response, Response.GetSize(), 0);
	Response.Clear();

	ResetData();
	RecvData();
	send(ClientSocket, Data, MAX_SIZEOF_PACKET, 0);

	delete[] Data;
	return 0;
}

int Login(SOCKET ClientSocket, int& PlayerNumber)
{
	int offset = 0;
	int temp = 0;
	char* Data = new char[MAX_SIZEOF_PACKET];
	
	RecvData();
	Packet LoginStart = Packet(Data, offset);
	Player player = Player(LoginStart.GetString(offset, temp));
	//这里其实是个bug，但能用
	bool IsStored = false;
	for (int i = 0; i < MaxPlayerIndex; i++)
	{
		if (EmptyPlayerSlot[i] == true)
		{
			OnlinePlayer[i] = player;
			EmptyPlayerSlot[i] = false;
			IsStored = true;
			break;
		}
	}
	if (!IsStored)
	{
		OnlinePlayer[MaxPlayerIndex] = player;
		MaxPlayerIndex++;
	}

	//TODO: 正版验证

	PacketBuilder LoginSuccess(0x02);
	LoginSuccess.Add(std::string("ef79a1fe-8ead-4fb2-ac06-ec328482ecfe"));//玩家UUID
	LoginSuccess.Add(player.GetName());//玩家昵称
	send(ClientSocket, LoginSuccess, MAX_SIZEOF_PACKET, 0);

	PacketBuilder JoinGame(0x23);
	JoinGame.Add(1);//实体ID
	JoinGame.Add((uint8_t)1);//游戏模式
	JoinGame.Add(0);//维度
	JoinGame.Add((uint8_t)0);//难度
	JoinGame.Add((uint8_t)2);//最多玩家
	JoinGame.Add(std::string("default"));//地图模式
	JoinGame.Add(false);//更少的调试信息
	send(ClientSocket, JoinGame, MAX_SIZEOF_PACKET, 0);

	delete[] Data;
	return 0;
}
