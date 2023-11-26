#pragma once
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

//C++ std lib
#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <fstream>
#include <cstdint>
#include <stdio.h>
#include <stdlib.h>
#include <codecvt>

//windows lib
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>

//external lib
#include <binlog/binlog.hpp>
#include <binlog/TextOutputStream.hpp>
#include <json/json.h>
#include <json/json.h>
#include <curl\curl.h>