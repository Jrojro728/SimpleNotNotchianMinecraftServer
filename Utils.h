#include <json/json.h>
#define BOOST_NETWORK_ENABLE_HTTPS
#include <boost/network/protocol/http/client.hpp>

struct VersionInfo
{
	std::string VersionName;
	int ProtocolID;
	int PacketVer;
	Json::Value PacketChange;
};

VersionInfo GetVersion(int VersionID);