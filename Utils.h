#pragma once
#pragma warning(disable : 4996)

#include <json/json.h>
#include <fstream>
#include <openssl/sha.h>
#include <boost/asio.hpp>

struct VersionInfo
{
	std::string VersionName;
	int PacketVer;
	Json::Value PacketChange;
};

// https://gist.github.com/madmongo1/53c303c6fe8de64f93adc014c7671d51
// MC独特的hex摘要🤣
struct daft_hash_impl
{
    daft_hash_impl()
        : ctx_{}
    {
        SHA1_Init(&ctx_);
    }

    daft_hash_impl(daft_hash_impl const&) = delete;
    daft_hash_impl(daft_hash_impl&&) = delete;
    daft_hash_impl& operator=(daft_hash_impl const&) = delete;
    daft_hash_impl& operator=(daft_hash_impl&&) = delete;
    ~daft_hash_impl() {}

    //我把boost::asio::const_buffer换成了自带的string,因为感觉有点脱裤子放屁。
    void update(std::string in) { SHA1_Update(&ctx_, in.data(), in.size()); }

    std::string finalise();

private:
    SHA_CTX ctx_;
};

/// <summary>
/// 获取版本信息
/// </summary>
/// <param name="VersionID">版本代码</param>
/// <returns>版本信息</returns>
VersionInfo GetVersion(int VersionID);

/// <summary>
/// 写Status Json Response
/// </summary>
/// <param name="VersionName">版本名</param>
/// <param name="VersionID">版本ID</param>
/// <returns></returns>
std::string GetStatusJson(std::string VersionName, int VersionID);
