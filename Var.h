#pragma once
#include "pch.h"

/// <summary>
/// 编码VarInt
/// </summary>
/// <param name="OriginalNumber">原数值</param>
/// <param name="buf">数据存储位置</param>
/// <param name="Size">转换之后数据的大小</param>
/// <returns>VarLong变量</returns>
int8_t* EncodeVarInt(long long OriginalNumber, int8_t* Buffer, int &Size);
/// <summary>
/// 解码VarInt
/// </summary>
/// <param name="VarLong">要解码的VarInt变量</param>
/// <param name="Size">转换之后数据的大小</param>
/// <returns>解码后的数值</returns>
long long DecodeVarInt(int8_t* VarInt, int &Size);

/// <summary>
/// 从网上复制的翻转字节序函数
/// </summary>
/// <param name="pData">数据</param>
/// <param name="length">类型长度</param>
void EndianSwap(int8_t* pData, int length);

/// <summary>
/// 获取随机新UUID
/// </summary>
/// <returns>获取到的UUID</returns>
std::string GetRandomUUID();

/// <summary>
/// 将字符串转换成utf8格式
/// </summary>
/// <param name="gbkData">要转换的字符串</param>
/// <returns>转换后的字符串</returns>
std::string String2UTF8(const std::string& gbkData);