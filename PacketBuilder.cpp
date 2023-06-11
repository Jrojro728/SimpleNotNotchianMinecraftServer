#include "PacketBuilder.h"
#include <vcruntime_string.h>

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
