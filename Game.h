#pragma once

#include "WinSock2Usage.h"
#include "Packet.h"
#include "Utils.h"
#include "PacketBuilder.h"
#include "Logger.h"

//方便的预处理器函数
#define AddTempToOffset() offset += temp
#define ResetOffset() offset = 0
#define ResetData(Size) memset(Data, 0, Size)
#define RecvData(Size) recv(ClientSocket, Data, Size, 0)

//数据结构

struct Position
{

};

struct Player
{
	std::string Name;
	std::string UUID;

	Player(std::string name, std::string uuid)
	{
		Name = name;
		UUID = uuid;
	}
};

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
/// <param name="ClientSocket">客户端连接</param>
/// <param name="VersionName">版本号</param>
/// <param name="ProtocolNum">版本编号</param>
/// <returns>状态码</returns>
int Status(SOCKET ClientSocket, const std::string& VersionName, int& ProtocolNum);

/// <summary>
/// 登陆阶段
/// </summary>
/// <param name="ClientSocket">客户端连接</param>
/// <param name="ThreadPlayer">当前线程的玩家</param>
/// <returns></returns>
int Login(SOCKET ClientSocket, int& ThreadPlayer);

/// <summary>
/// Play阶段
/// </summary>
/// <param name="ClientSocket">客户端连接</param>
/// <param name="ThreadPlayer">本线程处理的玩家</param>
/// <returns>永不返回所以只能是错误码</returns>
int Play(SOCKET ClientSocket, int& ThreadPlayer);
