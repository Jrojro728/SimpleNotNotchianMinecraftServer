//Utils.cpp: 一些不可分类的函数

#include "Utils.h"
#include <algorithm>
#include <array>
#include <boost/algorithm/string/case_conv.hpp>
#include <openssl/bn.h>
#include <curl/curl.h>

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

	//TODO: 把所有在线玩家列出
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

size_t req_reply(void* ptr, size_t size, size_t nmemb, void* stream)
{
	std::string* str = (std::string*)stream;
	(*str).append((char*)ptr, size * nmemb);
	return size * nmemb;
}

std::string GetPlayerUUID(std::string PlayerName)
{
	//https://blog.csdn.net/qq_37781464/article/details/102497139
	// curl初始化  
	CURL* curl = curl_easy_init();
	// curl返回值 
	CURLcode res;

	std::string Response;
	if (curl)
	{
		// set params
		//设置curl的请求头
		struct curl_slist* header_list = NULL;
		header_list = curl_slist_append(header_list, "User-Agent: Mozilla/5.0 (Windows NT 10.0; WOW64; Trident/7.0; rv:11.0) like Gecko");
		header_list = curl_slist_append(header_list, "Content-Type:application/x-www-form-urlencoded; charset=UTF-8");
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header_list);

		//不接收响应头数据0代表不接收 1代表接收
		curl_easy_setopt(curl, CURLOPT_HEADER, 0);

		//设置请求为post请求
		curl_easy_setopt(curl, CURLOPT_POST, 1);

		//设置请求的URL地址
		curl_easy_setopt(curl, CURLOPT_URL, "https://tenapi.cn/v2/mc");
		//设置post请求的参数
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "uid=jrojro");

		//设置ssl验证
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false);

		//CURLOPT_VERBOSE的值为1时，会显示详细的调试信息
		curl_easy_setopt(curl, CURLOPT_VERBOSE, 0);

		curl_easy_setopt(curl, CURLOPT_READFUNCTION, NULL);

		//设置数据接收和写入函数
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, req_reply);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&Response);

		curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);

		//设置超时时间
		curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 6);
		curl_easy_setopt(curl, CURLOPT_TIMEOUT, 6);

		// 开启post请求
		res = curl_easy_perform(curl);
	}
	else
		throw "CURL error";
	//释放curl 
	curl_easy_cleanup(curl);
	//https://blog.csdn.net/qq_37781464/article/details/102497139 end

	//Json解析
	Json::Reader Parser;
	Json::Value Root;
	if (Parser.parse(Response, Root))
	{
		//返回错误检查
		if (Root["code"].asInt() != 200)
			throw "get failed";
		if (Root["data"]["name"].asCString() != PlayerName)
			throw "result not equal to request";

		return Root["data"]["id"].asCString();
	}
	throw "jsoncpp error";
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
