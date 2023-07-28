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
	VersionName = GetVersion(ProtocolNum);
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
	std::string PlayerName = LoginStart.GetString(offset, temp);
	xg::Guid PlayerUUID;
	try
	{
		PlayerUUID = xg::Guid(GetPlayerUUID(PlayerName));
	}
	catch (const char* e)
	{
		return 1;
	}
	Player player = Player(PlayerName, PlayerUUID);
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
	LoginSuccess.Add(PlayerUUID.str());//玩家UUID
	LoginSuccess.Add(PlayerName);//玩家昵称
	send(ClientSocket, LoginSuccess, MAX_SIZEOF_PACKET, 0);
	LoginSuccess.Clear();

	PacketBuilder JoinGame(0x23);
	JoinGame.Add<int>(1);//实体ID
	JoinGame.Add<int8_t>(Creative);//游戏模式
	JoinGame.Add<int>(Overworld);//维度
	JoinGame.Add<int8_t>(peaceful);//难度
	JoinGame.Add<int8_t>((int8_t)2);//最多玩家
	JoinGame.Add(std::string("default"));//地图模式
	JoinGame.Add<bool>(false);//更少的调试信息
	send(ClientSocket, JoinGame, MAX_SIZEOF_PACKET, 0);
	JoinGame.Clear();

	PacketBuilder SpawnPosition(0x46);
	SpawnPosition.Add(Location(0, 0, 0).GetAll());
	send(ClientSocket, SpawnPosition, MAX_SIZEOF_PACKET, 0);
	SpawnPosition.Clear();

	PacketBuilder PlayerAbilities(0x2C);
	PlayerAbilities.Add((int8_t)0x04);
	PlayerAbilities.Add((float)10);
	PlayerAbilities.Add((float)10);
	send(ClientSocket, PlayerAbilities, MAX_SIZEOF_PACKET, 0);
	PlayerAbilities.Clear();

	ResetData();
	RecvData();
	ResetOffset();

	delete[] Data;
	return 0;
}
