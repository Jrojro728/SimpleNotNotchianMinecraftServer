#pragma once
#include "Packet.h"

class PacketBuilder
{
public:
	//构造函数
	PacketBuilder() : PacketBuilder(0) {};
	PacketBuilder(int ID);

	operator char* ()
	{
		return (char*)GetData();
	}

	operator int()
	{
		return (int) GetSize();
	}

	void Clear() { delete[] Data; };

	//增加数据
	template<typename T>
	void Add(T Data);
	void Add(std::string Data);
	
	//获取制造的数据包
	Packet GetPacket(int& offset);
	//获取Data
	int8_t* GetData() { return Data; };
	size_t GetSize() { return Size; };

private:
	int8_t* Data;
	size_t Size, RealSize;
	int ID;
};

template<typename T>
inline void PacketBuilder::Add(T Data){
	int SizeDataSize, SizeofData = sizeof(T), TempSize = RealSize;
	int8_t* SizeData = new int8_t[4], *Temp = (int8_t*)this->Data + (Size - RealSize);
	char* CharData = new char[SizeofData];
	Size -= (Size - RealSize);
	
	CharData = (char*)&Data;
	Size += SizeofData, RealSize += SizeofData;

	EndianSwap((int8_t *)CharData, SizeofData);
	SizeData = EncodeVarInt(RealSize, SizeData, SizeDataSize);
	Size += SizeDataSize;
	
	delete[] this->Data;
	this->Data = new int8_t[Size + 1];
	memset(this->Data, 0, Size + 1);
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
		this->Data[SizeDataSize + TempSize + i] = (int8_t)CharData[i];
	}
}
