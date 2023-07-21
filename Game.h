#pragma once

#include "WinSock2Usage.h"
#include "Packet.h"
#include "Utils.h"
#include "PacketBuilder.h"

//玩家结构
struct Player
{
public:
	Player(std::string name = "jrojro") : name(name) {};

	void operator=(Player& player) {
		for (int i = 0; i < 4; i++)
		{
			armor[i] = player.armor[i];
		}
		for (int x = 0; x < 9; x++)
		{
			for (int y = 0; y < 4; y++)
			{
				Inventory[x][y];
			}
		}
		health = player.health;
		hungry = player.hungry;
		name = player.name;
	};

	void SetItem(short column, short row, int item) { Inventory[column][row] = item; };
	void SetHealth(short Health) { health = Health; };
	void SetHungry(short Hungry) { hungry = Hungry; };
	void SetArmor(short number, int item) { armor[number] = item; };

	std::string GetName() { return name; };
	int GetInventory(short column, short row) { return Inventory[column][row]; };
	short GetHealth() { return health; };
	short GetHungry() { return hungry; };
	int GetArmor(short number) { return armor[number]; };

private:
	std::string name;
	int Inventory[9][4];
	short health, hungry;
	int armor[4];
};

//方便的预处理器函数
#define AddTempToOffset() offset += temp
#define ResetOffset() offset = 0
#define ResetData() memset(Data, 0, MAX_SIZEOF_PACKET)
#define RecvData() recv(ClientSocket, Data, MAX_SIZEOF_PACKET, 0)

//游戏正常阶段处理
DWORD NormalProcess(LPVOID lpParam);

//游戏阶段处理
/// <summary>
/// HandShake阶段
/// </summary>
/// <param name="ClientSocket">客户端套接字</param>
/// <param name="VersionName">版本号</param>
/// <param name="ProtocolNum">版本编号</param>
/// <returns>状态码</returns>
int HandShake(SOCKET ClientSocket, std::string& VersionName, int& ProtocolNum);

/// <summary>
/// Status阶段
/// </summary>
/// <param name="ClientSocket">客户端套接字</param>
/// <param name="VersionName">版本号</param>
/// <param name="ProtocolNum">版本编号</param>
/// <returns>状态码</returns>
int Status(SOCKET ClientSocket, const std::string& VersionName, int& ProtocolNum);

/// <summary>
/// 登录阶段
/// </summary>
/// <param name="ClientSocket">客户端套接字</param>
/// <returns>状态码</returns>
int Login(SOCKET ClientSocket, int& PlayerNumber);
