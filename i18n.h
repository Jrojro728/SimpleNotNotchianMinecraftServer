#pragma once
#include "pch.h"

using std::string, std::pair;
enum What
{

};
//支持的语言
std::map<int, string> SupportLanguage({ pair<int, string>(0x0804, "zh_CN" ), pair<int, string>(0x0009, "en") });
//已经打开的翻译文件
std::map<int, string> AlreadyOpenFile;
//已经打开的翻译文件的语言代码
std::vector<int> AlreadyOpenLanguageFileCode;
int NumberOfSupportLanguage = 2;

/// <summary>
/// 获取指定语言的字符串
/// </summary>
/// <param name="LanguageCode">语言代码</param>
/// <param name="KeyName">要获取内容的键名</param>
/// <param name="Output">获取到的字符串</param>
/// <returns>状态码</returns>
int GetTranslateString(int LanguageCode, std::string KeyName, std::string& Output);
std::string GetTranslateString(int LanguageCode, std::string KeyName)
{
	string Output;
	GetTranslateString(LanguageCode, KeyName, Output);
	return Output;
}
