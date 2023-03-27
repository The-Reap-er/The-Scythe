//
// Created by grimreaper on 3/26/23.
//

#ifndef THE_SCYTHE_WINDOWS_TCP_CLIENT_HPP
#define THE_SCYTHE_WINDOWS_TCP_CLIENT_HPP

#include "networking_includes.hpp"

namespace TheScythe {
    namespace Core {
        class windows_Socket {
        protected:

        public:

            static char windows_tcp_connect_ipv4(const char *ip, suint port, char *msg);

        };

#ifdef INFO_OS_WINDOWS
        typedef SOCKET Handle;
        typedef int Size;


        const static Handle Invalid = INVALID_SOCKET;
        const static int Error = SOCKET_ERROR;

        char windows_Socket::windows_tcp_connect_ipv4(const char *ip, suint port, char *msg) {
                WSAData wsaData;
                WORD DllVersion = MAKEWORD(2, 1);
                if (WSAStartup(DllVersion, &wsaData) != 0) {
                    std::cout << "Winsock Connection Failed!" << std::endl;
                    exit(1);
                }

                std::string getInput = "";
                SOCKADDR_IN addr;
                int addrLen = sizeof(addr);
                IN_ADDR ipvalue;
                addr.sin_addr.s_addr = inet_addr(ip);
                addr.sin_port = htons(port);
                addr.sin_family = AF_INET;

                SOCKET connection = socket(AF_INET, SOCK_STREAM, NULL);
                if (connect(connection, (SOCKADDR*)&addr, addrLen) == 0) {
                    std::cout << "Connected!" << std::endl;
                    getline(std::cin, getInput);
                    exit(0);
                }
                else {
                    std::cout << "Error Connecting to Host" << std::endl;
                    exit(1);
                }
                return 0;

        }
#endif
    }
}

#endif //THE_SCYTHE_WINDOWS_TCP_CLIENT_HPP
