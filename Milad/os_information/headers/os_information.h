#pragma once

#include "require.h"

namespace windows
{
	double get_os_information();
	BOOL is_windows_server();
	BOOL is_windows_x64();
	std::string os_architecture();
	std::string version();
	std::string username();
	std::string hostname();
	std::string domainname();
	std::string uuid_as_target_id();
	std::vector<std::string> ip_internal();
	std::vector<std::string> processes_list();
	std::vector<std::string> mac_address();
}