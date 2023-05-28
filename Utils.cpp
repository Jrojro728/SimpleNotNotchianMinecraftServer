#include "Utils.h"

VersionInfo GetVersion(int ProtocolID)
{
	using namespace boost::network;
	using namespace boost::network::http;

	VersionInfo Result;

	//解析网址
	client Client;
	client::request Request("https://gitlab.bixilon.de/bixilon/minosoft/-/raw/master/src/main/resources/assets/minosoft/mapping/versions.json");
	Request << header("Connection", "close");
	client::response Response = Client.get(Request);
	std::string ResponseStr = body(Response);

	//Json解析
	Json::Reader Parser;
	Json::Value Root;
	if (Parser.parse(ResponseStr, Root))
	{
		for (int i = 0; i < INT32_MAX; i++)
		{
			char* String;
			itoa(i, String, 10);
			if (Root[String]["protocol_id"].asInt() == ProtocolID)
			{
				Result.ProtocolID = ProtocolID;
				Result.VersionName = Root[String]["name"].asCString();
				try
				{
					Result.PacketVer = Root[String]["packet"].asInt();
					Result.PacketChange = 0;
				}
				catch (const std::exception&)
				{
					Result.PacketVer = 0;
					Result.PacketChange = Root[String]["packet"];
				}
				return Result;
			}
		}
	}

	throw "Unknown ProtocolID";
}