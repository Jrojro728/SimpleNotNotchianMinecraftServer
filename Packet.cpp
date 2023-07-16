//Packet.cpp: 数据包处理
#include "Packet.h"

Packet::Packet(char* DataBase, int& offset)
{
	int temp = 0;
	Size = DecodeVarInt((int8_t*)DataBase, offset);
	ID = DecodeVarInt((int8_t*)DataBase + offset, temp);
	offset += temp;

	Data = (int8_t*)DataBase;
}

long long Packet::GetVarInt(int Start, int& Size)
{
	int8_t* temp = new int8_t[8];
	for (int i = 0; i < 8; i++)
	{
		temp[i] = Data[Start + i];
	}

	int Result = DecodeVarInt(temp, Size);
	delete[] temp;
	return Result;
}

std::string Packet::GetString(int Start, int &Size)
{
	int VarIntSize = 0;
	int8_t* VarInt = new int8_t[4];
	for (int i = 0; i < 4; i++)
	{
		VarInt[i] = Data[i + Start];
	}

	int offset = 0;
	int StringSize = DecodeVarInt(VarInt, offset);
	delete[] VarInt;
	char* temp = new char[StringSize + 1];
	memset(temp, 0, StringSize + 1);
	for (int i = 0; i < StringSize; i++)
	{
		temp[i] = Data[i + Start + offset];
	}

	Size = StringSize + offset;

	std::string Result = std::string(temp, Size);
	delete[] temp;
	return Result;
}