#pragma once
#include "pch.h"

using std::string, std::pair;
enum What
{

};
//֧�ֵ�����
std::map<int, string> SupportLanguage({ pair<int, string>(0x0804, "zh_CN" ), pair<int, string>(0x0009, "en") });
//�Ѿ��򿪵ķ����ļ�
std::map<int, string> AlreadyOpenFile;
//�Ѿ��򿪵ķ����ļ������Դ���
std::vector<int> AlreadyOpenLanguageFileCode;
int NumberOfSupportLanguage = 2;

/// <summary>
/// ��ȡָ�����Ե��ַ���
/// </summary>
/// <param name="LanguageCode">���Դ���</param>
/// <param name="KeyName">Ҫ��ȡ���ݵļ���</param>
/// <param name="Output">��ȡ�����ַ���</param>
/// <returns>״̬��</returns>
int GetTranslateString(int LanguageCode, std::string KeyName, std::string& Output);
std::string GetTranslateString(int LanguageCode, std::string KeyName)
{
	string Output;
	GetTranslateString(LanguageCode, KeyName, Output);
	return Output;
}
