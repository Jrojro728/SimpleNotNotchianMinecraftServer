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
int DecodeVarInt(int8_t* VarInt);

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
long long DecodeVarLong(int8_t* VarLong);