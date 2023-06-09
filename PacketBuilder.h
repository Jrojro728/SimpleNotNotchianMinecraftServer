#pragma once

#include "Var.h"

class PacketBuilder
{
public:
	//���캯��
	PacketBuilder() : PacketBuilder(0) {};
	PacketBuilder(int ID);

	template<typename T>
	void Add(T Data);

private:
	char* Data;
	int Size;
	int ID;
};

template<typename T>
inline void PacketBuilder::Add(T Data)
{

}
