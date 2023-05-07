#pragma once
#include <cstdint>

/// <summary>
/// ����VarInt
/// </summary>
/// <param name="OriginalNumber">ԭ��ֵ</param>
/// <returns>VarInt����</returns>
int8_t* EncodeVarInt(int OriginalNumber, int8_t* buf);
/// <summary>
/// ����VarInt
/// </summary>
/// <param name="VarLong">Ҫ�����VarInt����</param>
/// <returns>��������ֵ</returns>
int DecodeVarInt(int8_t* VarInt);

/// <summary>
/// ����VarLong
/// </summary>
/// <param name="OriginalNumber">ԭ��ֵ</param>
/// <returns>VarLong����</returns>
int8_t* EncodeVarLong(long long OriginalNumber, int8_t* buf);
/// <summary>
/// ����VarLong
/// </summary>
/// <param name="VarLong">Ҫ�����VarLong����</param>
/// <returns>��������ֵ</returns>
long long DecodeVarLong(int8_t* VarLong);