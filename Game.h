#pragma once

#include "WinSock2Usage.h"
#include "Packet.h"
#include "Utils.h"
#include "PacketBuilder.h"

int offset = 0, temp = 0;
char Data[MAX_SIZEOF_PACKET];
SOCKET ClientSocket;

#define AddTempToOffset() offset += temp
#define ResetOffset() offset = 0
#define ResetData() memset(Data, 0, MAX_SIZEOF_PACKET)
#define RecvData() recv(ClientSocket, Data, MAX_SIZEOF_PACKET, 0)

int HandShake(std::string& VersionName, int& ProtocolNum);
int Status(const std::string& VersionName, int& ProtocolNum);