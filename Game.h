#pragma once

#include "WinSock2Usage.h"
#include "Packet.h"
#include "Utils.h"
#include "PacketBuilder.h"

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
