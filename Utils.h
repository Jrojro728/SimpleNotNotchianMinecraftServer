#include <json/json.h>
#define BOOST_NETWORK_ENABLE_HTTPS
#include <boost/network/protocol/http/client.hpp>

#include <fstream>

struct VersionInfo
{
	std::string VersionName;
	std::string Type;
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
/// <param name="VersionName"></param>
/// <param name="VersionID"></param>
/// <returns></returns>
std::string GetStatusJson(std::string VersionName, int VersionID);