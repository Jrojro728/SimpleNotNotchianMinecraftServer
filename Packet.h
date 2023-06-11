#pragma once

#define MAX_SIZEOF_PACKET 131071
#pragma warning(disable: 4244)

#include <cstdint>
#include <string>

#include "Var.h"

class Packet
{
public:
	//内联函数
	Packet() { throw "unexpected param"; }
	~Packet() {	}

	//构造函数
	Packet(char* DataBase, int& offset);

	int GetSize() { return Size; };
	int GetID() { return ID; };
	char* GetData() { return (char*)Data; };
	//获取包中的变量,都要指定位置(字节单位),和获取到的Var的大小
	long long GetVarInt(int Start, int& Size);
	std::string GetString(int Start, int& Size);
	template<typename T>
	T GetAnyType(int Start, int& Size);

private:
	int Size;
	int ID;
	int8_t* Data;
};

template<typename T>
T Packet::GetAnyType(int Start, int& Size)
{
	Size = sizeof(T);
	int8_t* tTemp = new int8_t[Size];
	for (int i = 0; i < Size; i++)
	{
		tTemp[i] = Data[Start + i];
	}
	EndianSwap(tTemp, Size);

	T Result = *(T*)tTemp;
	delete[] tTemp;
	return Result;
}