#include "Packet.h"

Packet::Packet(char* DataBase, int& offset)
{
	int temp = 0;
	Size = DecodeVarInt((int8_t*)DataBase, offset);
	ID = DecodeVarInt((int8_t*)DataBase + offset, temp);
	offset += temp;

	Data = (int8_t*)DataBase;
}

int Packet::GetVarInt(int Start, int& Size)
{
	int8_t* temp = new int8_t[4];
	for(int i = 0; i < 4; i++)
	{
		temp[i] = Data[Start + i];
	}
	return DecodeVarInt(temp, Size);
}

long long Packet::GetVarLong(int Start, int& Size)
{
	int8_t* temp = new int8_t[8];
	for (int i = 0; i < 8; i++)
	{
		temp[i] = Data[Start + i];
	}
	return DecodeVarLong(temp, Size);
}

std::string Packet::GetString(int Start, int &Size)
{
	int8_t* VarInt = new int8_t[Size];
	for (int i = 0; i < Size; i++)
	{
		VarInt[i] = Data[i + Start];
	}

	int offset = 0;
	Size = DecodeVarInt(VarInt, offset);
	char* temp = new char[Size];
	for (int i = 0; i < Size; i++)
	{
		temp[i] = Data[i + Start + offset];
	}
	
	return std::string(temp, Size);
}
