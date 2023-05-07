#pragma once

#define MAX_SIZEOF_PACKET 131071

#include <cstdint>
#include <string>

#include "Var.h"

class Packet
{
public:
	//��������
	Packet() { throw "unexpected param"; }
	~Packet() {	}

	//���캯��
	Packet(char* DataBase);

	int8_t* GetData() { return Data; };
	//��ȡ���еı���,��Ҫָ��λ��(�ֽڵ�λ)
	int GetVarInt(int Start, int End);
	long long GetVarLong(int Start, int End);
	std::string GetString(int Start, int End);

private:
	int Size;
	int ID;
	int8_t* Data;
};
