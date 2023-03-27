#pragma once

#define _CRT_SECURE_NO_WARNINGS

// Windows and C Specefic Headers

#include <winsock2.h>
#include <Windows.h>
#include <tlhelp32.h>
#include <tchar.h>
#include <iphlpapi.h>
#include <stdio.h>
#include <ws2tcpip.h>

// C++ Standard Headers
#include <iostream>
#include <string>
#include <random>
#include <sstream>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>
#include <fstream>
#include <cstdlib>

// Third-party header files
#include <json/json.h>
#include <json/value.h>

// User-defined Headers
#include "os_information.h"

// Statuically linked libraries
#pragma comment(lib, "Iphlpapi.lib")
#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "userenv.lib")
#pragma comment(lib, "crypt32.lib")

// Program Constants
#define UNLEN 1024

static std::random_device              rd;
static std::mt19937                    gen(rd());
static std::uniform_int_distribution<> dis(0, 15);
static std::uniform_int_distribution<> dis2(8, 11);