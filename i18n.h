#pragma once
#include <string>

enum MyEnum
{
	zh_CN = 0x0804;
};

/// <summary>
/// 获取指定语言的字符串
/// </summary>
/// <param name="LanguageCode">语言代码</param>
/// <param name="KeyName">要获取内容的键名</param>
/// <param name="Output">获取到的字符串</param>
/// <returns>状态码</returns>
int GetTranslateString(int LanguageCode, std::string KeyName, std::string& Output);
