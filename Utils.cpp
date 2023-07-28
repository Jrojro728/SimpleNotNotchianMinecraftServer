//Utils.cpp: 一些不可分类的函数

#include "Utils.h"
#include <algorithm>
#include <array>
#include <boost/algorithm/string/case_conv.hpp>
#include <openssl/bn.h>
#include <curl/curl.h>

const char * TempSolution("{ \"753\":{\"name\":\"1.16.3\"},\"752\":{\"name\":\"1.16.3-rc1\"},\"751\":{\"name\":\"1.16.2\"},\"750\":{\"name\":\"1.16.2-rc2\"},\"749\":{\"name\":\"1.16.2-rc1\"},\"748\":{\"name\":\"1.16.2-pre3\"},\"746\":{\"name\":\"1.16.2-pre2\"},\"744\":{\"name\":\"1.16.2-pre1\"},\"743\":{\"name\":\"20w30a\"},\"741\":{\"name\":\"20w29a\"},\"740\":{\"name\":\"20w28a\"},\"738\":{\"name\":\"20w27a\"},\"736\":{\"name\":\"1.16.1\"},\"735\":{\"name\":\"1.16\"},\"734\":{\"name\":\"1.16-rc1\"},\"733\":{\"name\":\"1.16-pre8\"},\"732\":{\"name\":\"1.16-pre7\"},\"730\":{\"name\":\"1.16-pre6\"},\"729\":{\"name\":\"1.16-pre5\"},\"727\":{\"name\":\"1.16-pre4\"},\"725\":{\"name\":\"1.16-pre3\"},\"722\":{\"name\":\"1.16-pre2\"},\"721\":{\"name\":\"1.16-pre1\"},\"719\":{\"name\":\"20w22a\"},\"718\":{\"name\":\"20w21a\"},\"717\":{\"name\":\"20w20b\"},\"716\":{\"name\":\"20w20a\"},\"715\":{\"name\":\"20w19a\"},\"714\":{\"name\":\"20w18a\"},\"713\":{\"name\":\"20w17a\"},\"712\":{\"name\":\"20w16a\"},\"711\":{\"name\":\"20w15a\"},\"710\":{\"name\":\"20w14a\"},\"709\":{\"name\":\"20w13b\"},\"708\":{\"name\":\"20w13a\"},\"707\":{\"name\":\"20w12a\"},\"706\":{\"name\":\"20w11a\"},\"705\":{\"name\":\"20w10a\"},\"704\":{\"name\":\"20w09a\"},\"703\":{\"name\":\"20w08a\"},\"702\":{\"name\":\"20w07a\"},\"701\":{\"name\":\"20w06a\"},\"578\":{\"name\":\"1.15.2\"},\"577\":{\"name\":\"1.15.2-pre2\"},\"576\":{\"name\":\"1.15.2-pre1\"},\"575\":{\"name\":\"1.15.1\"},\"574\":{\"name\":\"1.15.1-pre1\"},\"573\":{\"name\":\"1.15\"},\"572\":{\"name\":\"1.15-pre7\"},\"571\":{\"name\":\"1.15-pre6\"},\"570\":{\"name\":\"1.15-pre5\"},\"569\":{\"name\":\"1.15-pre4\"},\"567\":{\"name\":\"1.15-pre3\"},\"566\":{\"name\":\"1.15-pre2\"},\"565\":{\"name\":\"1.15-pre1\"},\"564\":{\"name\":\"19w46b\"},\"563\":{\"name\":\"19w46a\"},\"562\":{\"name\":\"19w45b\"},\"561\":{\"name\":\"19w45a\"},\"560\":{\"name\":\"19w44a\"},\"559\":{\"name\":\"19w42a\"},\"558\":{\"name\":\"19w41a\"},\"557\":{\"name\":\"19w40a\"},\"556\":{\"name\":\"19w39a\"},\"555\":{\"name\":\"19w38b\"},\"554\":{\"name\":\"19w38a\"},\"553\":{\"name\":\"19w37a\"},\"552\":{\"name\":\"19w36a\"},\"551\":{\"name\":\"19w35a\"},\"550\":{\"name\":\"19w34a\"},\"498\":{\"name\":\"1.14.4\"},\"497\":{\"name\":\"1.14.4-pre7\"},\"496\":{\"name\":\"1.14.4-pre6\"},\"495\":{\"name\":\"1.14.4-pre5\"},\"494\":{\"name\":\"1.14.4-pre4\"},\"493\":{\"name\":\"1.14.4-pre3\"},\"492\":{\"name\":\"1.14.4-pre2\"},\"491\":{\"name\":\"1.14.4-pre1\"},\"490\":{\"name\":\"1.14.3\"},\"489\":{\"name\":\"1.14.3-pre4\"},\"488\":{\"name\":\"1.14.3-pre3\"},\"487\":{\"name\":\"1.14.3-pre2\"},\"486\":{\"name\":\"1.14.3-pre1\"},\"485\":{\"name\":\"1.14.2\"},\"484\":{\"name\":\"1.14.2-pre4\"},\"483\":{\"name\":\"1.14.2-pre3\"},\"482\":{\"name\":\"1.14.2-pre2\"},\"481\":{\"name\":\"1.14.2-pre1\"},\"480\":{\"name\":\"1.14.1\"},\"479\":{\"name\":\"1.14.1-pre2\"},\"478\":{\"name\":\"1.14.1-pre1\"},\"477\":{\"name\":\"1.14\"},\"476\":{\"name\":\"1.14-pre5\"},\"475\":{\"name\":\"1.14-pre4\"},\"474\":{\"name\":\"1.14-pre3\"},\"473\":{\"name\":\"1.14-pre2\"},\"472\":{\"name\":\"1.14-pre1\"},\"471\":{\"name\":\"19w14b\"},\"470\":{\"name\":\"19w14a\"},\"469\":{\"name\":\"19w13b\"},\"468\":{\"name\":\"19w13a\"},\"467\":{\"name\":\"19w12b\"},\"466\":{\"name\":\"19w12a\"},\"465\":{\"name\":\"19w11b\"},\"464\":{\"name\":\"19w11a\"},\"463\":{\"name\":\"19w09a\"},\"462\":{\"name\":\"19w08b\"},\"461\":{\"name\":\"19w08a\"},\"460\":{\"name\":\"19w07a\"},\"459\":{\"name\":\"19w06a\"},\"458\":{\"name\":\"19w05a\"},\"457\":{\"name\":\"19w04b\"},\"456\":{\"name\":\"19w04a\"},\"455\":{\"name\":\"19w03c\"},\"454\":{\"name\":\"19w03b\"},\"453\":{\"name\":\"19w03a\"},\"452\":{\"name\":\"19w02a\"},\"451\":{\"name\":\"18w50a\"},\"450\":{\"name\":\"18w49a\"},\"449\":{\"name\":\"18w48b\"},\"448\":{\"name\":\"18w48a\"},\"447\":{\"name\":\"18w47b\"},\"446\":{\"name\":\"18w47a\"},\"445\":{\"name\":\"18w46a\"},\"444\":{\"name\":\"18w45a\"},\"443\":{\"name\":\"18w44a\"},\"442\":{\"name\":\"18w43c\"},\"441\":{\"name\":\"18w43b\"},\"440\":{\"name\":\"18w43a\"},\"404\":{\"name\":\"1.13.2\"},\"403\":{\"name\":\"1.13.2-pre2\"},\"402\":{\"name\":\"1.13.2-pre1\"},\"401\":{\"name\":\"1.13.1\"},\"400\":{\"name\":\"1.13.1-pre2\"},\"399\":{\"name\":\"1.13.1-pre1\"},\"398\":{\"name\":\"18w33a\"},\"397\":{\"name\":\"18w32a\"},\"396\":{\"name\":\"18w31a\"},\"395\":{\"name\":\"18w30b\"},\"394\":{\"name\":\"18w30a\"},\"393\":{\"name\":\"1.13\"},\"392\":{\"name\":\"1.13-pre10\"},\"391\":{\"name\":\"1.13-pre9\"},\"390\":{\"name\":\"1.13-pre8\"},\"389\":{\"name\":\"1.13-pre7\"},\"388\":{\"name\":\"1.13-pre6\"},\"387\":{\"name\":\"1.13-pre5\"},\"386\":{\"name\":\"1.13-pre4\"},\"385\":{\"name\":\"1.13-pre3\"},\"384\":{\"name\":\"1.13-pre2\"},\"383\":{\"name\":\"1.13-pre1\"},\"382\":{\"name\":\"18w22c\"},\"381\":{\"name\":\"18w22b\"},\"380\":{\"name\":\"18w22a\"},\"379\":{\"name\":\"18w21b\"},\"378\":{\"name\":\"18w21a\"},\"377\":{\"name\":\"18w20c\"},\"376\":{\"name\":\"18w20b\"},\"375\":{\"name\":\"18w20a\"},\"374\":{\"name\":\"18w19b\"},\"373\":{\"name\":\"18w19a\"},\"372\":{\"name\":\"18w16a\"},\"371\":{\"name\":\"18w15a\"},\"370\":{\"name\":\"18w14b\"},\"369\":{\"name\":\"18w14a\"},\"368\":{\"name\":\"18w11a\"},\"367\":{\"name\":\"18w10d\"},\"366\":{\"name\":\"18w10c\"},\"365\":{\"name\":\"18w10b\"},\"364\":{\"name\":\"18w10a\"},\"363\":{\"name\":\"18w09a\"},\"362\":{\"name\":\"18w08b\"},\"361\":{\"name\":\"18w08a\"},\"360\":{\"name\":\"18w07c\"},\"359\":{\"name\":\"18w07b\"},\"358\":{\"name\":\"18w07a\"},\"357\":{\"name\":\"18w06a\"},\"356\":{\"name\":\"18w05a\"},\"355\":{\"name\":\"18w03b\"},\"354\":{\"name\":\"18w03a\"},\"353\":{\"name\":\"18w02a\"},\"352\":{\"name\":\"18w01a\"},\"351\":{\"name\":\"17w50a\"},\"350\":{\"name\":\"17w49b\"},\"349\":{\"name\":\"17w49a\"},\"348\":{\"name\":\"17w48a\"},\"347\":{\"name\":\"17w47b\"},\"346\":{\"name\":\"17w47a\"},\"345\":{\"name\":\"17w46a\"},\"344\":{\"name\":\"17w45b\"},\"343\":{\"name\":\"17w45a\"},\"342\":{\"name\":\"17w43b\"},\"341\":{\"name\":\"17w43a\"},\"340\":{\"name\":\"1.12.2\"},\"339\":{\"name\":\"1.12.2-pre2\"},\"338\":{\"name\":\"1.12.1\"},\"337\":{\"name\":\"1.12.1-pre1\"},\"336\":{\"name\":\"17w31a\"},\"335\":{\"name\":\"1.12\"},\"334\":{\"name\":\"1.12-pre7\"},\"333\":{\"name\":\"1.12-pre6\"},\"332\":{\"name\":\"1.12-pre5\"},\"331\":{\"name\":\"1.12-pre4\"},\"330\":{\"name\":\"1.12-pre3\"},\"329\":{\"name\":\"1.12-pre2\"},\"328\":{\"name\":\"1.12-pre1\"},\"327\":{\"name\":\"17w18b\"},\"326\":{\"name\":\"17w18a\"},\"325\":{\"name\":\"17w17b\"},\"324\":{\"name\":\"17w17a\"},\"323\":{\"name\":\"17w16b\"},\"322\":{\"name\":\"17w16a\"},\"321\":{\"name\":\"17w15a\"},\"320\":{\"name\":\"17w14a\"},\"319\":{\"name\":\"17w13b\"},\"318\":{\"name\":\"17w13a\"},\"317\":{\"name\":\"17w06a\"},\"316\":{\"name\":\"1.11.2\"},\"315\":{\"name\":\"1.11\"},\"314\":{\"name\":\"1.11-pre1\"},\"313\":{\"name\":\"16w44a\"},\"312\":{\"name\":\"16w42a\"},\"311\":{\"name\":\"16w41a\"},\"310\":{\"name\":\"16w40a\"},\"309\":{\"name\":\"16w39c\"},\"308\":{\"name\":\"16w39b\"},\"307\":{\"name\":\"16w39a\"},\"306\":{\"name\":\"16w38a\"},\"305\":{\"name\":\"16w36a\"},\"304\":{\"name\":\"16w35a\"},\"303\":{\"name\":\"16w33a\"},\"302\":{\"name\":\"16w32b\"},\"301\":{\"name\":\"16w32a\"},\"210\":{\"name\":\"1.10.2\"},\"205\":{\"name\":\"1.10-pre2\"},\"204\":{\"name\":\"1.10-pre1\"},\"203\":{\"name\":\"16w21b\"},\"202\":{\"name\":\"16w21a\"},\"201\":{\"name\":\"16w20a\"},\"110\":{\"name\":\"1.9.4\"},\"109\":{\"name\":\"1.9.3-pre1\"},\"108\":{\"name\":\"1.9.1\"},\"107\":{\"name\":\"1.9.1-pre1\"},\"106\":{\"name\":\"1.9-pre4\"},\"105\":{\"name\":\"1.9-pre3\"},\"104\":{\"name\":\"1.9-pre2\"},\"103\":{\"name\":\"1.9-pre1\"},\"102\":{\"name\":\"16w07b\"},\"101\":{\"name\":\"16w07a\"},\"100\":{\"name\":\"16w06a\"},\"99\":{\"name\":\"16w05b\"},\"98\":{\"name\":\"16w05a\"},\"97\":{\"name\":\"16w04a\"},\"96\":{\"name\":\"16w03a\"},\"95\":{\"name\":\"16w02a\"},\"94\":{\"name\":\"15w51b\"},\"93\":{\"name\":\"15w51a\"},\"92\":{\"name\":\"15w50a\"},\"91\":{\"name\":\"15w49b\"},\"90\":{\"name\":\"15w49a\"},\"89\":{\"name\":\"15w47c\"},\"88\":{\"name\":\"15w47b\"},\"87\":{\"name\":\"15w47a\"},\"86\":{\"name\":\"15w46a\"},\"85\":{\"name\":\"15w45a\"},\"84\":{\"name\":\"15w44b\"},\"83\":{\"name\":\"15w44a\"},\"82\":{\"name\":\"15w43c\"},\"81\":{\"name\":\"15w43b\"},\"80\":{\"name\":\"15w43a\"},\"79\":{\"name\":\"15w42a\"},\"78\":{\"name\":\"15w41b\"},\"77\":{\"name\":\"15w41a\"},\"76\":{\"name\":\"15w40b\"},\"75\":{\"name\":\"15w40a\"},\"74\":{\"name\":\"15w39c\"},\"73\":{\"name\":\"15w38b\"},\"72\":{\"name\":\"15w38a\"},\"71\":{\"name\":\"15w37a\"},\"70\":{\"name\":\"15w36d\"},\"69\":{\"name\":\"15w36c\"},\"68\":{\"name\":\"15w36b\"},\"67\":{\"name\":\"15w36a\"},\"66\":{\"name\":\"15w35e\"},\"65\":{\"name\":\"15w35d\"},\"64\":{\"name\":\"15w35c\"},\"63\":{\"name\":\"15w35b\"},\"62\":{\"name\":\"15w35a\"},\"61\":{\"name\":\"15w34d\"},\"60\":{\"name\":\"15w34c\"},\"59\":{\"name\":\"15w34b\"},\"58\":{\"name\":\"15w34a\"},\"57\":{\"name\":\"15w33c\"},\"56\":{\"name\":\"15w33b\"},\"55\":{\"name\":\"15w33a\"},\"54\":{\"name\":\"15w32c\"},\"53\":{\"name\":\"15w32b\"},\"52\":{\"name\":\"15w32a\"},\"51\":{\"name\":\"15w31c\"},\"50\":{\"name\":\"15w31b\"},\"49\":{\"name\":\"15w31a\"},\"47\":{\"name\":\"1.8.9\"},\"46\":{\"name\":\"1.8-pre3\"},\"45\":{\"name\":\"1.8-pre2\"},\"44\":{\"name\":\"1.8-pre1\"},\"43\":{\"name\":\"14w34d\"},\"42\":{\"name\":\"14w34c\"},\"41\":{\"name\":\"14w34b\"},\"40\":{\"name\":\"14w34a\"},\"39\":{\"name\":\"14w33c\"},\"38\":{\"name\":\"14w33b\"},\"37\":{\"name\":\"14w33a\"},\"36\":{\"name\":\"14w32d\"},\"35\":{\"name\":\"14w32c\"},\"34\":{\"name\":\"14w32b\"},\"33\":{\"name\":\"14w32a\"},\"32\":{\"name\":\"14w31a\"},\"31\":{\"name\":\"14w30c\"},\"30\":{\"name\":\"14w30b\"},\"29\":{\"name\":\"14w29a\"},\"28\":{\"name\":\"14w28b\"},\"27\":{\"name\":\"14w28a\"},\"26\":{\"name\":\"14w27b\"},\"25\":{\"name\":\"14w26c\"},\"24\":{\"name\":\"14w26b\"},\"23\":{\"name\":\"14w26a\"},\"22\":{\"name\":\"14w25b\"},\"21\":{\"name\":\"14w25a\"},\"20\":{\"name\":\"14w21b\"},\"19\":{\"name\":\"14w21a\"},\"18\":{\"name\":\"14w20b\"},\"17\":{\"name\":\"14w19a\"},\"16\":{\"name\":\"14w18b\"},\"15\":{\"name\":\"14w17a\"},\"14\":{\"name\":\"14w11b\"},\"13\":{\"name\":\"14w10c\"},\"12\":{\"name\":\"14w08a\"},\"11\":{\"name\":\"14w07a\"},\"10\":{\"name\":\"14w06b\"},\"9\":{\"name\":\"14w05b\"},\"8\":{\"name\":\"14w04b\"},\"7\":{\"name\":\"14w04a\"},\"6\":{\"name\":\"14w03b\"},\"5\":{\"name\":\"1.7.10\"},\"4\":{\"name\":\"1.7.5\"},\"3\":{\"name\":\"1.7.1-pre\"},\"2\":{\"name\":\"13w43a\"},\"1\":{\"name\":\"13w42b\"},\"0\":{\"name\":\"13w41b\"}}");

//1.16.1之前的版本获取信息的办法
std::string GetOlderVersion(int ProtocolID);

std::string GetVersion(int ProtocolID)
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
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "uid=" + PlayerName);

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
		if (Root["data"]["name"].asCString() != PlayerName.c_str())
			throw "result not equal to request";

		return Root["data"]["id"].asCString();
	}
	throw "jsoncpp error";
}

std::string GetOlderVersion(int ProtocolID)
{

	//Json解析
	Json::Reader Parser;
	Json::Value Root;
	if (Parser.parse(TempSolution, Root))
	{
		char TempStr[4]{ 0 };
		_itoa_s(ProtocolID, TempStr, 10);
		return Root[TempStr]["name"].asCString();
	}

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
