#pragma once

#include "Var.h"

class PacketBuilder
{
public:
	//构造函数
	PacketBuilder() : PacketBuilder(0) {};
	PacketBuilder(int ID);

	template<typename T>
	void Add(T* Data);

private:
	int8_t* Data;
	int Size, RealSize;
	int ID;
};

template<typename T>
inline void PacketBuilder::Add(T* Data){
	int SizeDataSize, SizeofData = sizeof(T), TempSize = RealSize;
	int8_t* SizeData = new int8_t[4], *Temp = (int8_t*)this->Data + 1;
	char* CharData = new char[SizeofData];
	CharData = (char*)Data;
	Size += SizeofData, RealSize += SizeofData;

	EndianSwap((int8_t *)CharData, SizeofData);
	SizeData = EncodeVarInt(RealSize, SizeData, SizeDataSize);
	
	this->Data = new int8_t[Size];
	for (size_t i = 0; i < SizeDataSize; i++)
	{
		this->Data[i] = SizeData[i];
	}
	for (size_t i = 0; i < TempSize; i++)
	{
		this->Data[SizeDataSize + i] = Temp[i];
	}
	for (size_t i = 0; i < SizeofData; i++)
	{
		this->Data[SizeDataSize + 1 + i] = (int8_t)CharData[i];
	}
}
