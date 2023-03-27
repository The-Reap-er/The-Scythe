//
// Created by grimreaper on 3/18/23.
//

#ifndef THESCYTHE_LINUX_TCP_CLIENT_HPP
#define THESCYTHE_LINUX_TCP_CLIENT_HPP
#include "networking_includes.hpp"
namespace TheScythe
{
    namespace Core
    {
        class linux_Socket
                {
        protected:

        public:
            /// DNS domain lookup (using IPv4)
            static std::string dnsLookup4(const std::string &domain);
            /// Tcp Connect
            static char linux_tcp_connect_ipv4(const char * ip, suint port, char * msg);
            static char linux_tcp_connect_ipv6(const char * ipv6, suint port, char * msg);
            typedef int Handle;
            typedef socklen_t Size;
            typedef struct sockaddr_in Address;
            const static Handle Invalid = -1;
            const static int Error = -1;
        };


        /// edit later on windows


        std::string linux_Socket::dnsLookup4(const std::string &domain)
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

        char linux_Socket::linux_tcp_connect_ipv4(const char * ip, suint port, char * msg) {
            int status, client_fd, valread;
            struct sockaddr_in serv_addr;
            char buffer[1024] = { 0 };
            if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
                std::string err = "\n linux_Socket creation Fucking Failed ! \n";
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

        char linux_Socket::linux_tcp_connect_ipv6(const char *ipv6, suint port, char *msg) {

            int status, client_fd, valread;
            struct sockaddr_in6 server_addr;
            int ret;
            char buffer[1024] = { 0 };
            if ((client_fd = socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP)) < 0) {
                std::string err = "\n linux_Socket creation Fucking Failed ! \n";
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

#endif //THESCYTHE_LINUX_TCP_CLIENT_HPP
