#pragma once
#include <string>

enum MyEnum
{
	zh_CN = 0x0804;
};

/// <summary>
/// ��ȡָ�����Ե��ַ���
/// </summary>
/// <param name="LanguageCode">���Դ���</param>
/// <param name="KeyName">Ҫ��ȡ���ݵļ���</param>
/// <param name="Output">��ȡ�����ַ���</param>
/// <returns>״̬��</returns>
int GetTranslateString(int LanguageCode, std::string KeyName, std::string& Output);
