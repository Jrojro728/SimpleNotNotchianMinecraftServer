#include "Utils.h"

//1.16.1之前的版本获取信息的办法
VersionInfo GetOlderVersion(int ProtocolID);

VersionInfo GetVersion(int ProtocolID)
{
	GetOlderVersion(ProtocolID);
	using namespace boost::network;
	using namespace boost::network::http;

	//解析网址
	client Client;
	client::request Request("https://gitlab.bixilon.de/bixilon/minosoft/-/raw/master/src/main/resources/assets/minosoft/mapping/versions.json");
	Request << header("Connection", "close");
	client::response Response = Client.get(Request);
	std::string ResponseStr = body(Response);

	if (ProtocolID <= 753)
	{

	}

	throw "Unknown ProtocolID";
}

VersionInfo GetOlderVersion(int ProtocolID)
{
	std::ifstream JsonFile("OldVersionJson.json");

	JsonFile.seekg(0, std::ios::end);
	int len = JsonFile.tellg();
	JsonFile.seekg(0, std::ios::beg);
	char* FileCStr= new char[len];
	std::string OlderVersionJsonStr;
	
	JsonFile.read(FileCStr, len);
	OlderVersionJsonStr = FileCStr;

	//Json解析
	Json::Reader Parser;
	Json::Value Root;
	if (Parser.parse(OlderVersionJsonStr, Root))
	{
		VersionInfo Result;
		char TempStr[4]{ 0 };
		_itoa_s(ProtocolID, TempStr, 10);
		Result.VersionName = Root[TempStr]["name"].asCString();
		try
		{
			Result.Type = Root[TempStr]["type"].asCString();
			Result.PacketVer = Root[TempStr]["packet"].asInt();
		}
		catch (const std::exception&)
		{
			Json::Value::Members types = Root[TempStr].getMemberNames();            //得到子节点

			
		}

		return VersionInfo();
	}
}