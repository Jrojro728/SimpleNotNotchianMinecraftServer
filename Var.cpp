//Var.cpp: 协议变量相关的一些东西
#include "Var.h"
#include <json/json.h>
#include <curl\curl.h>
#include <codecvt>

//实现来自 https://zhuanlan.zhihu.com/p/84250836

size_t req_reply(void* ptr, size_t size, size_t nmemb, void* stream);

int8_t* EncodeVarInt(long long OriginalNumber, int8_t* buf, int &Size)
{
	Size = 0;

	for (Size = 0; OriginalNumber > 127; Size++)
	{
		buf[Size] = 0x80 | uint8_t(OriginalNumber & 0x7F);
		OriginalNumber >>= 7;
	}

	buf[Size] = uint8_t(OriginalNumber);
	Size++;
	return buf;
}

long long DecodeVarInt(int8_t* VarLong, int& Size)
{
	int x{}, n = 0;
	for (unsigned shift = 0; shift < 32; shift += 7)
	{
		if (n >= sizeof(VarLong))
			return 0;

		uint64_t b = VarLong[n];
		n++;

		x |= (b & 0x7f) << shift;
		if ((b & 0x80) == 0)
		{
			Size = n;
			return x;
		}
	}
	throw "VarInt is to big";
}

//https://www.cnblogs.com/wuyepeng/p/9833273.html
//如果出错了别怪我
void EndianSwap(int8_t* pData, int length)
{
	int i, cnt, end, start;
	cnt = length / 2;
	start = 0;
	end = 0 + length - 1;
	int8_t tmp;
	for (i = 0; i < cnt; i++)
	{
		tmp = pData[start + i];
		pData[start + i] = pData[end - i];
		pData[end - i] = tmp;
	}
}

std::string StringToUTF8(const std::string& gbkData)
{
	const char* GBK_LOCALE_NAME = "CHS";  //GBK在windows下的locale name(.936, CHS ), linux下的locale名可能是"zh_CN.GBK"

	std::wstring_convert<std::codecvt<wchar_t, char, mbstate_t>>
		conv(new std::codecvt<wchar_t, char, mbstate_t>(GBK_LOCALE_NAME));
	std::wstring wString = conv.from_bytes(gbkData);    // string => wstring

	std::wstring_convert<std::codecvt_utf8<wchar_t>> convert;
	std::string utf8str = convert.to_bytes(wString);     // wstring => utf-8

	return utf8str;
}

std::string GetRandomUUID()
{
	std::string Result;
	//curl初始化  
	CURL* curl = curl_easy_init();
	// curl返回值 
	CURLcode res;
	if (curl)
	{
		//不接收响应头数据0代表不接收 1代表接收
		curl_easy_setopt(curl, CURLOPT_HEADER, 0);

		//设置请求的URL地址 
		curl_easy_setopt(curl, CURLOPT_URL, "https://www.uuidtools.com/api/generate/v4/count/1");

		//设置ssl验证
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false);

		//CURLOPT_VERBOSE的值为1时，会显示详细的调试信息
		curl_easy_setopt(curl, CURLOPT_VERBOSE, 0);

		curl_easy_setopt(curl, CURLOPT_READFUNCTION, NULL);

		//设置数据接收函数
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, req_reply);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&Result);

		curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);

		//设置超时时间
		curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 6); // set transport and time out time  
		curl_easy_setopt(curl, CURLOPT_TIMEOUT, 6);

		// 开启请求  
		res = curl_easy_perform(curl);
	}

	// 释放curl 
	curl_easy_cleanup(curl);

	Json::Reader Parser;
	Json::Value Root;
	if (Parser.parse(Result, Root))
	{
		return Root[0].asCString();
	}
	throw "Json Parser Error";
}

size_t req_reply(void* ptr, size_t size, size_t nmemb, void* stream)
{
	//在注释的里面可以打印请求流，cookie的信息
	//cout << "----->reply" << endl;
	std::string* str = (std::string*)stream;
	//cout << *str << endl;
	(*str).append((char*)ptr, size * nmemb);
	return size * nmemb;
}