//
// Created by grimreaper on 3/26/23.
//

#ifndef THE_SCYTHE_NETWORKING_INCLUDES_HPP
#define THE_SCYTHE_NETWORKING_INCLUDES_HPP

#include "../../The-Scythe.hpp"

#if defined(INFO_OS_WINDOWS)
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment (lib, "Ws2_32.lib")
#include <iostream>
#include <string.h>
#include <sstream>
#include <WinSock2.h>
#include <WS2tcpip.h>

#else
#include <string>
#include <cstring>
#include <stdint.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <unistd.h>
#endif

#endif //THE_SCYTHE_NETWORKING_INCLUDES_HPP
