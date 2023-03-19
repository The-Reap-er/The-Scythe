//
// Created by grimreaper on 3/18/23.
//

#ifndef THESCYTHE_TCP_CLIENT_HPP
#define THESCYTHE_TCP_CLIENT_HPP

#include "../../The-Scythe.hpp"

#if defined(INFO_OS_WINDOWS)
#pragma comment (lib, "Ws2_32.lib")
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <ws2tcpip.h>
#include <arpa/inet.h>
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


namespace TheScythe
{
    namespace Core
    {
        class Socket
                {
        protected:

        public:
            /// DNS domain lookup (using IPv4)
            static std::string dnsLookup4(const std::string &domain);
            /// Tcp Connect
            static char linux_tcp_connect_ipv4(const char * ip, suint port, char * msg);
            static char linux_tcp_connect_ipv6(const char * ipv6, suint port, char * msg);
            static char windows_tcp_connect_ipv4(const char * ip, suint port, char * msg);
            //static char linux_tcp_connect_ipv6(const char * ipv6, suint port, char * msg);




#ifdef INFO_OS_WINDOWS
            typedef SOCKET Handle;
            typedef int Size;
#else
            typedef int Handle;
            typedef socklen_t Size;
#endif

            typedef struct sockaddr_in Address;

#ifdef INFO_OS_WINDOWS
            const static Handle Invalid = INVALID_SOCKET;
            const static int Error = SOCKET_ERROR;
#else
            const static Handle Invalid = -1;
            const static int Error = -1;
#endif
        };

        /// edit later on windows
#ifdef INFO_OS_WINDOWS
        char Socket::windows_tcp_connect_ipv4(const char *ip, suint port, char *msg) {
            WSAData wsaData;
            WORD DllVersion = MAKEWORD(2, 1);
            if (WSAStartup(DllVersion, &wsaData) != 0) {
                cout << "Winsock Connection Failed!" << endl;
                exit(1);
            }

            string getInput = "";
            SOCKADDR_IN addr;
            int addrLen = sizeof(addr);
            IN_ADDR ipvalue;
            addr.sin_addr.s_addr = inet_addr("HOSTIPGOESHERE");
            addr.sin_port = htons(80);
            addr.sin_family = AF_INET;

            SOCKET connection = socket(AF_INET, SOCK_STREAM, NULL);
            if (connect(connection, (SOCKADDR*)&addr, addrLen) == 0) {
                cout << "Connected!" << endl;
                getline(cin, getInput);
                exit(0);
            }
            else {
                cout << "Error Connecting to Host" << endl;
                exit(1);
            }
            return 0;
        };
#endif
        std::string Socket::dnsLookup4(const std::string &domain)
        {

            hostent *m_hostent;
            m_hostent = gethostbyname( domain.c_str() );
            if( !m_hostent )
                return "";
            unsigned int addr;
            memcpy((void*)&addr, (void*)*m_hostent->h_addr_list, 4);

            return std::string(
                    inet_ntoa(
                            *(in_addr*)&addr
                    )
            );
        };

        char Socket::linux_tcp_connect_ipv4(const char * ip, suint port, char * msg) {
            int status, client_fd, valread;
            struct sockaddr_in serv_addr;
            char buffer[1024] = { 0 };
            if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
                std::string err = "\n Socket creation Fucking Failed ! \n";
                return -1;
            }
            serv_addr.sin_family = AF_INET;
            serv_addr.sin_port = htons(port);
            if (inet_pton(AF_INET, ip, &serv_addr.sin_addr)
                <= 0) {
                std::string err = "\nInvalid address/ Address not supported \n";
                return -1;
            }
            if ((status = connect(client_fd, (struct sockaddr*)&serv_addr,sizeof(serv_addr)))< 0) {
                std::string err = "\nConnection Failed \n";
                return -1;
            }

            /*send(client_fd, msg, strlen(msg), 0);
            valread = read(client_fd, buffer, 1024);
            close(client_fd);*/
            return client_fd;
        };

        char Socket::linux_tcp_connect_ipv6(const char *ipv6, suint port, char *msg) {

            int status, client_fd, valread;
            struct sockaddr_in6 server_addr;
            int ret;
            char buffer[1024] = { 0 };
            if ((client_fd = socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP)) < 0) {
                std::string err = "\n Socket creation Fucking Failed ! \n";
                return -1;
            }
            server_addr.sin6_family = AF_INET6;
            server_addr.sin6_port = htons(port);
            if (inet_pton(AF_INET6, ipv6, &server_addr.sin6_addr)
                <= 0) {
                std::string err = "\nInvalid address/ Address not supported \n";
                return -1;
            }
            if ((status = connect(client_fd, (struct sockaddr*)&server_addr,sizeof(server_addr)))< 0) {
                std::string err = "\nConnection Failed \n";
                return -1;
            }

            ret = write(client_fd, &msg, 1);
            if (ret == -1) {
                perror("write");
                close(client_fd);
                return EXIT_FAILURE;
            }

            /*send(client_fd, msg, strlen(msg), 0);
            valread = read(client_fd, buffer, 1024);
            std::cout << buffer;
            close(client_fd);*/
            return client_fd;
        }



    }
}

#endif //THESCYTHE_TCP_CLIENT_HPP
