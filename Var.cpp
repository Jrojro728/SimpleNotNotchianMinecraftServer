//Var.cpp: 协议变量相关的一些东西
#include "Var.h"

//实现来自 https://zhuanlan.zhihu.com/p/84250836

int8_t* EncodeVarInt(long long OriginalNumber, int8_t* buf, int &Size)
{
	Size = 0;

	for (Size = 0; OriginalNumber > 127; Size++)
	{
		buf[Size] = 0x80 | uint8_t(OriginalNumber & 0x7F);
		OriginalNumber >>= 7;
	}

	buf[Size] = uint8_t(OriginalNumber);
	Size++;
	return buf;
}

long long DecodeVarInt(int8_t* VarLong, int& Size)
{
	int x{}, n = 0;
	for (unsigned shift = 0; shift < 32; shift += 7)
	{
		if (n >= sizeof(VarLong))
			return 0;

		uint64_t b = VarLong[n];
		n++;

		x |= (b & 0x7f) << shift;
		if ((b & 0x80) == 0)
		{
			Size = n;
			return x;
		}
	}
	throw "VarInt is to big";
}

//https://www.cnblogs.com/wuyepeng/p/9833273.html
//如果出错了别怪我
void EndianSwap(int8_t* pData, int length)
{
	int i, cnt, end, start;
	cnt = length / 2;
	start = 0;
	end = 0 + length - 1;
	int8_t tmp;
	for (i = 0; i < cnt; i++)
	{
		tmp = pData[start + i];
		pData[start + i] = pData[end - i];
		pData[end - i] = tmp;
	}
}