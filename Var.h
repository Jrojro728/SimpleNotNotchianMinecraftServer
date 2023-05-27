#pragma once
#include <cstdint>

/// <summary>
/// 编码VarInt
/// </summary>
/// <param name="OriginalNumber">原数值</param>
/// <returns>VarInt变量</returns>
int8_t* EncodeVarInt(int OriginalNumber, int8_t* buf);
/// <summary>
/// 解码VarInt
/// </summary>
/// <param name="VarLong">要解码的VarInt变量</param>
/// <returns>解码后的数值</returns>
int DecodeVarInt(int8_t* VarInt, int &Size);

/// <summary>
/// 编码VarLong
/// </summary>
/// <param name="OriginalNumber">原数值</param>
/// <returns>VarLong变量</returns>
int8_t* EncodeVarLong(long long OriginalNumber, int8_t* buf);
/// <summary>
/// 解码VarLong
/// </summary>
/// <param name="VarLong">要解码的VarLong变量</param>
/// <returns>解码后的数值</returns>
long long DecodeVarLong(int8_t* VarLong, int &Size);

/// <summary>
/// 从网上复制的翻转字节序函数
/// </summary>
/// <param name="pData">数据</param>
/// <param name="startIndex"></param>
/// <param name="length"></param>
void EndianSwap(int8_t* pData, int length);