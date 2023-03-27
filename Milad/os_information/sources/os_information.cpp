#include "../headers/os_information.h"

// Function pointers and signtures
typedef BOOL(WINAPI* LPFN_ISWOW64PROCESS) (HANDLE, PBOOL);
LPFN_ISWOW64PROCESS fnIsWow64Process;

double windows::get_os_information()
{
	double windows_version_return = 0.0;
	NTSTATUS(WINAPI * RtlGetVersion)(LPOSVERSIONINFOEXW);
	OSVERSIONINFOEXW version;

	*(FARPROC*)&RtlGetVersion = GetProcAddress(GetModuleHandleA("ntdll"), "RtlGetVersion");

	if (NULL != RtlGetVersion)
	{
		version.dwOSVersionInfoSize = sizeof(version);
		RtlGetVersion(&version);
		windows_version_return = (double)version.dwMajorVersion;
	}
	return windows_version_return;
}

BOOL windows::is_windows_server()
{
	// Initialize the variables
	OSVERSIONINFOEX osvi = { 0 };
	DWORDLONG condition_mask = 0;
	int op = VER_EQUAL;

	// Initialize the OSVERSIONINFOEX structure.
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
	osvi.wProductType = VER_NT_SERVER;

	// Initialize the condition mask.
	VER_SET_CONDITION(condition_mask, VER_PRODUCT_TYPE, VER_EQUAL);

	// Perform the test.
	return VerifyVersionInfo(&osvi, VER_PRODUCT_TYPE, condition_mask);
}

BOOL windows::is_windows_x64()
{
	BOOL is_wow64_present = FALSE;
	fnIsWow64Process = (LPFN_ISWOW64PROCESS)GetProcAddress(GetModuleHandle(TEXT("kernel32")), "IsWow64Process");

	if (NULL != fnIsWow64Process)
	{
		if (!fnIsWow64Process(GetCurrentProcess(), &is_wow64_present))
		{
			"Unkown Architecture";
		}
	}
	return is_wow64_present;
}

std::string windows::os_architecture()
{
	if (!is_windows_x64())
		return "x64";
	else
		return "x86";
}

std::string windows::version()
{
	std::string os_info;
	os_info = std::to_string(get_os_information());

	os_info += " " + os_architecture();

	if (is_windows_server())
		os_info += " Server";
	else
		os_info += " Client";

	return os_info;
}

std::vector<std::string> windows::ip_internal()
{
	std::vector<std::string> ip_address;
	IP_ADAPTER_ADDRESSES* adapter_addresses(NULL);
	IP_ADAPTER_ADDRESSES* adapter(NULL);

	DWORD adapter_addresses_buffer_size = 16 * 1024;

	// Get adapter addresses
	for (int attempts = 0; attempts != 3; ++attempts) {
		adapter_addresses = (IP_ADAPTER_ADDRESSES*)malloc(adapter_addresses_buffer_size);

		DWORD error = ::GetAdaptersAddresses(AF_UNSPEC,
			GAA_FLAG_SKIP_ANYCAST |
			GAA_FLAG_SKIP_MULTICAST |
			GAA_FLAG_SKIP_DNS_SERVER |
			GAA_FLAG_SKIP_FRIENDLY_NAME,
			NULL,
			adapter_addresses,
			&adapter_addresses_buffer_size);

		if (ERROR_SUCCESS == error) {
			break;
		}
		else if (ERROR_BUFFER_OVERFLOW == error) {
			// Try again with the new size
			free(adapter_addresses);
			adapter_addresses = NULL;
			continue;
		}
		else {
			// Unexpected error code - log and throw
			free(adapter_addresses);
			adapter_addresses = NULL;
			ip_address.push_back("Unkown");
			return ip_address;
		}
	}
	int counter = 0;

	// Iterate through all of the adapters
	for (adapter = adapter_addresses; NULL != adapter; adapter = adapter->Next)
	{
		// Skip loopback adapters
		if (IF_TYPE_SOFTWARE_LOOPBACK == adapter->IfType) continue;

		// Parse all IPv4 addresses
		for (IP_ADAPTER_UNICAST_ADDRESS* address = adapter->FirstUnicastAddress; NULL != address; address = address->Next) {
			auto family = address->Address.lpSockaddr->sa_family;
			if (AF_INET == family) {
				SOCKADDR_IN* ipv4 = reinterpret_cast<SOCKADDR_IN*>(address->Address.lpSockaddr);
				char str_buffer[16] = { 0 };
				inet_ntop(AF_INET, &(ipv4->sin_addr), str_buffer, 16);
				ip_address.push_back(str_buffer);
				++counter;
			}
		}
	}

	free(adapter_addresses);
	adapter_addresses = NULL;
	return ip_address;
}

std::string windows::username()
{
	char username[UNLEN + 1];
	DWORD username_len = UNLEN + 1;

	GetUserNameA(username, &username_len);
	std::string username_standard(username);

	return username_standard;
}

std::string windows::hostname()
{
	FIXED_INFO* net_params = NULL;
	unsigned long length = 0;

	GetNetworkParams(net_params, &length);
	net_params = static_cast<FIXED_INFO*>(::operator new(length));
	GetNetworkParams(net_params, &length);

	if (!std::string(net_params->HostName).empty())
		return net_params->HostName;
	else
		return "Unkown";
}

std::string windows::domainname()
{
	FIXED_INFO* net_params = NULL;
	unsigned long length = 0;

	GetNetworkParams(net_params, &length);
	net_params = static_cast<FIXED_INFO*>(::operator new(length));
	GetNetworkParams(net_params, &length);

	if (!std::string(net_params->DomainName).empty())
		return net_params->DomainName;
	else
		return "workgroup";
}

std::string windows::uuid_as_target_id()
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

std::vector<std::string> windows::processes_list()
{
	HANDLE process_snap;
	PROCESSENTRY32 pe32;
	std::vector<std::string> processes_list;

	// Take a snapshot of all processes in the system.
	process_snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	// Set the size of the structure before using it.
	pe32.dwSize = sizeof(PROCESSENTRY32);

	// Retrieve information about the first process,
	// and exit if unsuccessful
	if (!Process32First(process_snap, &pe32))
	{
		// clean the snapshot object
		CloseHandle(process_snap);          
	}

	// Now walk the snapshot of processes, and
	// display information about each process in turn
	do
	{
		std::string processes(pe32.szExeFile);
		processes_list.push_back(processes);

	} while (Process32Next(process_snap, &pe32));

	CloseHandle(process_snap);
	return processes_list;
}

std::vector<std::string> windows::mac_address()
{
	PIP_ADAPTER_INFO adapter_info;
	DWORD buffer_length = sizeof(IP_ADAPTER_INFO);
	char* mac_address = (char*)malloc(18);
	std::vector<std::string> mac_addresses;

	adapter_info = (IP_ADAPTER_INFO*)malloc(sizeof(IP_ADAPTER_INFO));
	if (adapter_info == NULL) 
	{
		mac_addresses.push_back("NULL");
		return mac_addresses; 
	}

	// Make an initial call to GetAdaptersInfo to get the necessary size into the dwBufLen variable
	if (GetAdaptersInfo(adapter_info, &buffer_length) == ERROR_BUFFER_OVERFLOW) 
	{
		free(adapter_info);
		adapter_info = (IP_ADAPTER_INFO*)malloc(buffer_length);
		if (adapter_info == NULL) 
		{
			free(mac_address);
			mac_addresses.push_back("NULL");
			return mac_addresses;
		}
	}

	if (GetAdaptersInfo(adapter_info, &buffer_length) == NO_ERROR) 
	{
		// Contains pointer to current adapter info
		PIP_ADAPTER_INFO pointer_adapter_info = adapter_info;
		do 
		{
			// technically should look at pAdapterInfo->AddressLength and not assume it is 6.
			sprintf(mac_address, "%02X:%02X:%02X:%02X:%02X:%02X",
				pointer_adapter_info->Address[0], pointer_adapter_info->Address[1],
				pointer_adapter_info->Address[2], pointer_adapter_info->Address[3],
				pointer_adapter_info->Address[4], pointer_adapter_info->Address[5]);
			mac_addresses.push_back(mac_address);
			pointer_adapter_info = pointer_adapter_info->Next;
		} while (pointer_adapter_info);
	}
	free(adapter_info);
	return mac_addresses;
}
