//Utils.cpp: 一些不可分类的函数

#include "Utils.h"
#include <algorithm>
#include <array>
#include <boost/algorithm/string/case_conv.hpp>
#include <openssl/bn.h>

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

		try {
			Result.PacketVer = Root[TempStr]["packet"].asInt();
		}catch (const std::exception&){
			Result.PacketChange = Root[TempStr]["packet"];
		}

		delete[] FileCStr;
		return Result;
	}

	delete[] FileCStr;
	throw "Json Parser Error";
}

// https://gist.github.com/madmongo1/53c303c6fe8de64f93adc014c7671d51
std::string daft_hash_impl::finalise()
{
	auto result = std::string();

	auto buf = std::array< std::uint8_t, 20 >();
	SHA1_Final(buf.data(), &ctx_);

	// convert has to bignum
	BIGNUM* bn = BN_bin2bn(buf.data(), buf.size(), nullptr);

	// reset the hasher for next use
	SHA1_Init(&ctx_);

	// check for "negative" value
	if (BN_is_bit_set(bn, 159))
	{
		result += '-';

		// perform 1's compliment on the bignum's bits
		auto tmp = std::vector< unsigned char >(BN_num_bytes(bn));
		BN_bn2bin(bn, tmp.data());
		std::transform(tmp.begin(), tmp.end(), tmp.begin(), [](unsigned char b) { return ~b; });
		BN_bin2bn(tmp.data(), tmp.size(), bn);

		// add 1 "as-if" 2's compliment

		BN_add_word(bn, 1);
	}

	// convert to hex
	auto hex = BN_bn2hex(bn);

	// remove any leading zeroes except the last
	auto view = std::string_view(hex);
	while (view.size() && view[0] == '0')
		view = view.substr(1);

	// append the hex to the result
	result.append(view.begin(), view.end());
	OPENSSL_free(hex);
	BN_free(bn);

	// convert the hex to lower case
	boost::to_lower(result);
	return result;
}
