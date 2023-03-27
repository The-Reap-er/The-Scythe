#include "headers/require.h"

int main(int argc, char* argv[])
{
    auto uuid_target_id = windows::uuid_as_target_id();
    auto ip_addresses = windows::ip_internal();
    auto computer_name = windows::domainname();
    auto hostname = windows::hostname();
    auto username = windows::username();
    auto os = windows::version();
    auto processes_list = windows::processes_list();
    auto mac_address_list = windows::mac_address();

    Json::Value target_information;

    int ip_counter = 0;
    for each (auto ips in ip_addresses)
    {
        target_information[uuid_target_id]["1_IP"][ip_counter] = ips;
        ip_counter++;
    }

    target_information[uuid_target_id]["2_CName"] = computer_name;
    target_information[uuid_target_id]["3_HName"] = hostname;
    target_information[uuid_target_id]["4_UName"] = username;
    target_information[uuid_target_id]["5_OS"] = os;

    int process_counter = 0;
    for each(auto process in processes_list)
    {
        target_information[uuid_target_id]["6_Processes"][process_counter] = process;
        process_counter++;
    }

    int mac_counter = 0;
    for each (auto mac_address in mac_address_list)
    {
        target_information[uuid_target_id]["7_Mac"][mac_counter] = mac_address;
        mac_counter++;
    }

    std::cout << target_information << std::endl;

	return 0;
}