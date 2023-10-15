#pragma once

#include "pch.h"

/// <summary> 
/// 初始化Winsock2
/// </summary>
/// <param name="ListenSocket">要获取的客户端接口</param>
/// <returns>状态码</returns>
int InitWinsock2(SOCKET& ListenSocket);

int AcceptConnect(SOCKET& ListenSocket, SOCKET& ClientSocket);