#include "Packet.h"

Packet::Packet(char* DataBase)
{
	char* BaseBuf = new char[MAX_SIZEOF_PACKET];
	*BaseBuf = *DataBase;

	memset(DataBase + 1, 0, MAX_SIZEOF_PACKET - 1);
	Size = DecodeVarInt((int8_t*)DataBase);

	DataBase = BaseBuf;
	memset(DataBase, 0, 1);
	memset(DataBase + 2, 0, MAX_SIZEOF_PACKET - 2);
	std::string s(DataBase, MAX_SIZEOF_PACKET);
	s = s.substr(1);
	ID = DecodeVarInt((int8_t *)strtok(const_cast<char*>(s.c_str()), "\0"));
}

int Packet::GetVarInt(int Start, int End)
{
	return 0;
}

long long Packet::GetVarLong(int Start, int End)
{
	return 0;
}

std::string Packet::GetString(int Start, int End)
{
	return std::string();
}
