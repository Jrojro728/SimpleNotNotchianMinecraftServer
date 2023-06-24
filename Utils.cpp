#include "Utils.h"

//1.16.1之前的版本获取信息的办法
VersionInfo GetOlderVersion(int ProtocolID);

VersionInfo GetVersion(int ProtocolID)
{
	if (ProtocolID <= 753)
	{
		return GetOlderVersion(ProtocolID);
	}

	throw "newer than 1.16.3 is no support for now";
}

std::string GetStatusJson(std::string VersionName, int VersionID)
{
	Json::FastWriter FasterWriter;
	Json::Value Root;
	Json::Value Version;
	Version["name"] = VersionName; //版本名
	Version["protocol"] = VersionID; //协议号

	Json::Value Jrojro; //我自己的信息
	Json::Value Players;
	Players["max"] = 2; //最多玩家
	Players["online"] = 1; //在线玩家数
	Jrojro["name"] = "jrojro";
	Jrojro["id"] = "ef79a1fe-8ead-4fb2-ac06-ec328482ecfe";
	Players["sample"].append(Jrojro);

	Json::Value Description;
	Description["text"] = "This is a SimpleNotNotchianMinecraftServer";
	
	Root["description"] = Description;
	Root["players"] = Players;
	Root["version"] = Version;

	return FasterWriter.write(Root);
}

VersionInfo GetOlderVersion(int ProtocolID)
{
	std::ifstream JsonFile("OldVersionJson.json");

	JsonFile.seekg(0, std::ios::end);
	long long len = JsonFile.tellg();
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
		try{
			Result.Type = Root[TempStr]["type"].asCString();
		}catch (const std::exception&){}

		try {
			Result.PacketVer = Root[TempStr]["packet"].asInt();
		}catch (const std::exception&){
			Result.PacketChange = Root[TempStr]["packet"];
		}

		return Result;
	}

	throw "Json Parser Error";
}