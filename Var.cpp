#include "Var.h"

//实现来自 https://zhuanlan.zhihu.com/p/84250836

int8_t* EncodeVarInt(int OriginalNumber, int8_t* buf)
{
	int n = 0;

	for (n = 0; OriginalNumber > 127; n++)
	{
		buf[n] = 0x80 | uint8_t(OriginalNumber & 0x7F);
		OriginalNumber >>= 7;
	}

	buf[n] = uint8_t(OriginalNumber);
	n++;
	return buf;
}

int DecodeVarInt(int8_t* VarInt, int &Size)
{
	int x{}, n = 0;
	for (unsigned shift = 0; shift < 32; shift += 7)
	{
		if (n >= sizeof(VarInt))
			return 0;

		uint64_t b = VarInt[n];
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

int8_t* EncodeVarLong(long long OriginalNumber, int8_t* buf)
{
	int n = 0;

	for (n = 0; OriginalNumber > 127; n++)
	{
		buf[n] = 0x80 | uint8_t(OriginalNumber & 0x7F);
		OriginalNumber >>= 7;
	}

	buf[n] = uint8_t(OriginalNumber);
	n++;
	return buf;
}

long long DecodeVarLong(int8_t* VarLong, int& Size)
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