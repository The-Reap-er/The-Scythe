//
// Created by grimreaper on 3/19/23.
//
#include "modules/The-Scythe.hpp"
#include "modules/core/networking/tcp_client.hpp"
#include "modules/utils/crypto/decoder.hpp"
#include "modules/utils/crypto/encoder.hpp"
#include "modules/core/execution/execution.hpp"
//#include "modules/core/networking/http_client.hpp"

int main()
{
    std::string data = "hello mf";

    //TheScythe::Core::Http::http_post(url, fields);
/*
    std::cout << TheScythe::Core::Socket::dnsLookup4("google.com") << std::endl;

    std::cout << TheScythe::Utils::Encoder::b64Encode(data) << std::endl;
    std::string decode;
    TheScythe::Utils::Decoder::b64Decode(TheScythe::Utils::Encoder::b64Encode(data), decode);
    std::cout << decode;*/
    const char *ip = TheScythe::Utils::Decoder::bin_to_ip("1111111", "0", "0", "1").c_str();
    std::cout << TheScythe::Core::Socket::tcp_connect_ipv4(ip, 9002, "sddssdsd");
    const char * cmd = "ls";
    std::cout << TheScythe::Core::Execution::exec(cmd) << std::endl;
    /*const char *ipv6 = "::1";
    std::cout << TheScythe::Core::Socket::tcp_connect_ipv6(ipv6, 7002, "hi");
*/




}