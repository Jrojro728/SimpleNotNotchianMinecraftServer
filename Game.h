#pragma once

#include "WinSock2Usage.h"
#include "Packet.h"
#include "Utils.h"
#include "PacketBuilder.h"
#include <crossguid/guid.hpp>

//各种枚举
enum Gamemode : int8_t
{
	Survival = 0,
	Creative = 1,
	Adventure = 2,
	Spectator = 3,
	Hardcore = 0x8
};

enum Dimension : int
{
	Nether = -1,
	Overworld = 0,
	End = 1
};

enum Difficulty : int8_t
{
	peaceful = 0,
	easy = 1,
	normal = 2,
	hard = 3
};

//玩家结构
struct Player
{
public:
	Player(std::string name = "jrojro", xg::Guid uuid = xg::Guid("ef79a1fe-8ead-4fb2-ac06-ec328482ecfe")) : name(name), uuid(uuid) {};

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
		uuid = player.uuid;
	};

	void SetItem(short column, short row, int item) { Inventory[column][row] = item; };
	void SetHealth(short Health) { health = Health; };
	void SetHungry(short Hungry) { hungry = Hungry; };
	void SetArmor(short number, int item) { armor[number] = item; };

	std::string GetName() const { return name; };
	int GetInventory(short column, short row) const { return Inventory[column][row]; };
	short GetHealth() const { return health; };
	short GetHungry() const { return hungry; };
	int GetArmor(short number) const { return armor[number]; };
	xg::Guid GetUUID() const { return uuid; };

private:
	std::string name;
	int Inventory[9][4];
	short health, hungry;
	int armor[4];
	xg::Guid uuid;
};

//位置结构
struct Location
{
public:
	Location(int32_t X, int16_t Y, int32_t Z) { x = X; y = Y; z = Z; };

	int32_t GetX() { return x; };
	int16_t GetY() { return y; };
	int32_t GetZ() { return z; };
	uint64_t GetAll() { return ((static_cast<unsigned long long>(x & 0x3FFFFFF)) << 38) | ((static_cast<uint64_t>(y & 0xFFF)) << 26) | (z & 0x3FFFFFF); };

	void SetX(int32_t X) { x = X; };
	void SetY(int16_t Y) { y = Y; };
	void SetZ(int32_t Z) { z = Z; };
	void SetAll(uint64_t memory) {
		x = memory >> 38;
		y = (memory >> 26) & 0xFFF;
		z = memory << 38 >> 38;

		if (x >= 0x2000000) { x -= 0x4000000; }
		if (y >= 0x800) { y -= 0x1000; }
		if (z >= 0x2000000) { z -= 0x4000000; }
	};

private:
	int32_t x, z;
	int16_t y;
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
