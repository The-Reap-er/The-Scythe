#include "headers/require.h"

UINT XorStrings(PCHAR arg_input)
{
	INT counter = NULL;
	UINT hash_value = 0;
	UINT N = 0;
	while (counter = *arg_input++)
	{
		hash_value ^= ((N++ & 1) == NULL) ? ((hash_value << 5) ^ counter ^ (hash_value >> 1)) :
			(~((hash_value << 9) ^ counter ^ (hash_value >> 3)));

	}

	return (hash_value & 0x7FFFFFFF);
}

int main(int argc, char* argv[])
{
	UINT hashed_api = XorStrings("CreateThread");
	std::cout << "CreateThread: " << hashed_api << std::endl;

	hashed_api = XorStrings("CreateRemoteThread");
	std::cout << "CreateRemoteThread: " << hashed_api << std::endl;

	hashed_api = XorStrings("VirtualAlloc");
	std::cout << "VirtualAlloc: " << hashed_api << std::endl;

	hashed_api = XorStrings("VirtualAllocEx");
	std::cout << "VirtualAllocEx: " << hashed_api << std::endl;

	hashed_api = XorStrings("RtlMoveMemory");
	std::cout << "RtlMoveMemory: " << hashed_api << std::endl;

	hashed_api = XorStrings("VirtualProtect");
	std::cout << "VirtualProtect: " << hashed_api << std::endl;

	hashed_api = XorStrings("VirtualFree");
	std::cout << "VirtualFree: " << hashed_api << std::endl;

	return 0;
}