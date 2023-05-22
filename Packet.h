﻿#pragma once

#define MAX_SIZEOF_PACKET 131071

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

	int8_t* GetData() { return Data; };
	//获取包中的变量,都要指定位置(字节单位),和获取到的Var的大小
	int GetVarInt(int Start, int& Size);
	long long GetVarLong(int Start, int& Size);
	std::string GetString(int Start, int &Size);
	template<typename T>
	T GetAnyType(int Start);

private:
	int Size;
	int ID;
	int8_t* Data;
};

template<typename T>
T Packet::GetAnyType(int Start)
{
	int Size = sizeof(T);
	int8_t* tTemp = new int8_t[Size];
	for (int i = 0; i < Size; i++)
	{
		tTemp[i] = Data[Start + i];
	}

	return reinterpret_cast<T*>();
}