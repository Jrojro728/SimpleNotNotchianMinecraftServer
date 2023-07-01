#pragma once
#include <json/json.h>
#include <fstream>

struct VersionInfo
{
	std::string VersionName;
	int PacketVer;
	Json::Value PacketChange;
};

/// <summary>
/// 获取版本信息
/// </summary>
/// <param name="VersionID">版本代码</param>
/// <returns>版本信息</returns>
VersionInfo GetVersion(int VersionID);

/// <summary>
/// 写Status Json Response
/// </summary>
/// <param name="VersionName">版本名</param>
/// <param name="VersionID">版本ID</param>
/// <returns></returns>
std::string GetStatusJson(std::string VersionName, int VersionID);