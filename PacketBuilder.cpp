//PacketBuilder.cpp: 数据包创建器,可能有些数据溢出
//2024-1-27: 重构
#include "pch.h"
#include "PacketBuilder.h"

PacketBuilder::PacketBuilder(int ID)
{
	this->ID = ID;

	int IDSize = 0, SizeDataSize = 0;
	int8_t* IDData = new int8_t[4], *SizeData = new int8_t[4];
	IDData = EncodeVarInt(ID, IDData, IDSize);
	SizeData = EncodeVarInt(IDSize, SizeData, SizeDataSize);

	Size = static_cast<size_t>(IDSize) + static_cast<size_t>(SizeDataSize); //数据大小
	RealSize = IDSize;//数据包大小

	Data = new int8_t[Size + 1];//分配内存
	memset(Data, 0, Size + 1);//初始化内存
	for (size_t i = 0; i < SizeDataSize; i++) //写入数据长度
	{
		Data[i] = SizeData[i];
	}
	delete[] SizeData;
	for (size_t i = 0; i < IDSize; i++) //写入ID
	{
		Data[i + SizeDataSize] = IDData[i];
	}
	delete[] IDData;
}

void PacketBuilder::Add(std::string Data)
{
	int VarIntSize = 0, SizeDataSize = 0;
	size_t TempSize = RealSize, StringDataSize = 0;
	int8_t* StringSizeData = new int8_t[8], *Temp = new int8_t[Size - RealSize], * SizeData = new int8_t[4];
	strcpy((char*)Temp, (char*)this->Data + (Size - RealSize));
	delete[] this->Data;
	Size -= (Size - RealSize); //消除大小数据造成的混乱
	memset(StringSizeData, 0, 8);
	
	//字符串实际数据
	std::string UTF8String = String2UTF8(Data);
	const char* StringData = UTF8String.c_str();
	StringDataSize = strlen(StringData);
	Size += StringDataSize, RealSize += StringDataSize;

	//字符串数据长度
	StringSizeData = EncodeVarInt(StringDataSize, StringSizeData, VarIntSize);
	Size += VarIntSize, RealSize += VarIntSize;

	//数据包长度数据
	SizeData = EncodeVarInt(RealSize, SizeData, SizeDataSize);
	Size += SizeDataSize;

	this->Data = new int8_t[Size + 1];
	memset(this->Data, 0, Size + 1);
	for (size_t i = 0; i < SizeDataSize; i++)
	{
		this->Data[i] = SizeData[i];
	}
	delete[] SizeData;
	for (size_t i = 0; i < TempSize; i++)
	{
		this->Data[i + SizeDataSize] = Temp[i];
	}
	for (size_t i = 0; i < VarIntSize; i++)
	{
		this->Data[i + SizeDataSize + TempSize] = StringSizeData[i];
	}
	delete[] StringSizeData;
	for (size_t i = 0; i < Data.size(); i++)
	{
		this->Data[i + SizeDataSize + TempSize + VarIntSize] = StringData[i];
	}
}

Packet PacketBuilder::GetPacket(int& offset)
{
	return Packet((char *)Data, offset);
}
