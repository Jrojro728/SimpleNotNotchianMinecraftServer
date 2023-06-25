//PacketBuilder.cpp: 数据包创建器,可能有些数据溢出
#include "PacketBuilder.h"

PacketBuilder::PacketBuilder(int ID)
{
	this->ID = ID;

	int IDSize, SizeDataSize = 0;
	int8_t* IDData = new int8_t[4], *SizeData = new int8_t[4];
	IDData = EncodeVarInt(ID, IDData, IDSize);
	SizeData = EncodeVarInt(IDSize, SizeData, SizeDataSize);

	Size = IDSize + SizeDataSize;
	RealSize = IDSize;

	Data = new int8_t[Size + 1];
	memset(Data, 0, Size + 1);
	for (size_t i = 0; i < SizeDataSize; i++)
	{
		Data[i] = SizeData[i];
	}
	for (size_t i = 0; i < IDSize; i++)
	{
		Data[i + SizeDataSize] = IDData[i];
	}
}

void PacketBuilder::Add(long long Data)
{
	int VarIntSize = 0, TempSize = RealSize, SizeDataSize = 0;
	int8_t* VarInt = new int8_t[8], *Temp = this->Data + (Size - RealSize), *SizeData = new int8_t[4];
	Size -= (Size - RealSize);
	memset(VarInt, 0, 8);

	VarInt = EncodeVarInt(Data, VarInt, VarIntSize);
	Size += VarIntSize, RealSize += VarIntSize;

	SizeData = EncodeVarInt(RealSize, SizeData, SizeDataSize);
	Size += SizeDataSize;

	this->Data = new int8_t[Size + 1];
	memset(this->Data, 0, Size + 1);

	for (int i = 0; i < SizeDataSize; i++)
	{
		this->Data[i] = SizeData[i];
	}
	for (int i = 0; i < TempSize; i++)
	{
		this->Data[i + SizeDataSize] = Temp[i];
	}
	for (int i = 0; i < VarIntSize; i++)
	{
		this->Data[i + SizeDataSize + TempSize] = VarInt[i];
	}
}

void PacketBuilder::Add(std::string Data)
{
	int VarIntSize = 0, TempSize = RealSize, SizeDataSize = 0;
	int8_t* VarInt = new int8_t[8], * Temp = this->Data + (Size - RealSize), * SizeData = new int8_t[4];
	Size -= (Size - RealSize);
	memset(VarInt, 0, 8);

	VarInt = EncodeVarInt(Data.size(), VarInt, VarIntSize);
	Size += VarIntSize, RealSize += VarIntSize;

	const char* StringData = Data.c_str();
	Size += Data.size(), RealSize += Data.size();

	SizeData = EncodeVarInt(RealSize, SizeData, SizeDataSize);
	Size += SizeDataSize;

	this->Data = new int8_t[Size + 1];
	memset(this->Data, 0, Size + 1);

	for (int i = 0; i < SizeDataSize; i++)
	{
		this->Data[i] = SizeData[i];
	}
	for (int i = 0; i < TempSize; i++)
	{
		this->Data[i + SizeDataSize] = Temp[i];
	}
	for (int i = 0; i < VarIntSize; i++)
	{
		this->Data[i + SizeDataSize + TempSize] = VarInt[i];
	}
	for (int i = 0; i < Data.size(); i++)
	{
		this->Data[i + SizeDataSize + TempSize + VarIntSize] = StringData[i];
	}
}

Packet PacketBuilder::GetPacket(int& offset)
{
	return Packet((char *)Data, offset);
}
