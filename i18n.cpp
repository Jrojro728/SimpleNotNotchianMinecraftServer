#include "i18n.h"

int GetTranslateString(int LanguageCode, std::string KeyName, std::string& Output)
{
	//检查翻译文件是否已经打开
	bool AlreadyOpen = false;
	for (size_t i = 0; i < AlreadyOpenLanguageFileCode.size(); i++)
	{
		if (AlreadyOpenLanguageFileCode[i] == LanguageCode)
		{
			AlreadyOpen = true;
		}
	}
	
	if (AlreadyOpen)
	{
		//json解析
		Json::Reader Parser;
		Json::Value Root;
		if (Parser.parse(AlreadyOpenFile[LanguageCode], Root))
		{
			Output = Root[KeyName].asCString();
		}
		else
			return 1;
	}
	else
	{
		string FileName(SupportLanguage[LanguageCode]);
		FileName += ".json";

		std::ifstream TranslateFile(FileName);
		TranslateFile >> AlreadyOpenFile[LanguageCode];

		Json::Reader Parser;
		Json::Value Root;
		if (Parser.parse(AlreadyOpenFile[LanguageCode], Root))
		{
			Output = Root[KeyName].asCString();
		}
		else
			return 1;
	}
	
    return 0;
}
