#pragma once
#include <json/json.h>
#include <fstream>

/// <summary>
/// 获取版本信息
/// </summary>
/// <param name="VersionID">版本代码</param>
/// <returns>版本信息</returns>
std::string GetVersion(int VersionID);

/// <summary>
/// 写Status Json Response
/// </summary>
/// <param name="VersionName">版本名</param>
/// <param name="VersionID">版本ID</param>
/// <returns></returns>
std::string GetStatusJson(std::string VersionName, int VersionID);

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
std::string StringToUTF8(const std::string& gbkData);
