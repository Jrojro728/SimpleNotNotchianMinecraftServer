#pragma once
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

//C++ std lib
#include <codecvt>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

//windows lib
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>

//external lib
#include <binlog/binlog.hpp>
#include <binlog/TextOutputStream.hpp>
#include <curl\curl.h>
#include <json/json.h>
