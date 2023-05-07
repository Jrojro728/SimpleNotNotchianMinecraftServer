#pragma once

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
	Packet(char* DataBase);

	int8_t* GetData() { return Data; };
	//获取包中的变量,都要指定位置(字节单位)
	int GetVarInt(int Start, int End);
	long long GetVarLong(int Start, int End);
	std::string GetString(int Start, int End);

private:
	int Size;
	int ID;
	int8_t* Data;
};
