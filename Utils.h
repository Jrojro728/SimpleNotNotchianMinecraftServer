#include <json/json.h>
#define BOOST_NETWORK_ENABLE_HTTPS
#include <boost/network/protocol/http/client.hpp>

#include <fstream>

struct VersionInfo
{
	std::string VersionName;
	std::string Type;
	int PacketVer;
	std::vector<std::string> PacketChange;
};

/// <summary>
/// 获取版本信息
/// </summary>
/// <param name="VersionID">版本代码</param>
/// <returns>版本信息</returns>
VersionInfo GetVersion(int VersionID);