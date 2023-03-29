#include "../headers/obfuscation.h"


VOID obfuscation::load()
{
	if ((g_CallGate.User32 = GetModuleHandleW(L"USER32.DLL")) == ERROR) 
	{
		g_CallGate.User32 = LoadLibraryW(L"USER32.DLL");
	}

	if (g_CallGate.User32) 
	{
		g_CallGate._MessageBoxW = fnMessageBoxW(resolved_functions(g_CallGate.User32, HashMessageBoxW));
	}

	if ((g_CallGate.Kernel32 = GetModuleHandleW(L"Kernel32.DLL")) == ERROR) 
	{
		g_CallGate.Kernel32 = LoadLibraryW(L"Kernel32.DLL");
	}

	if (g_CallGate.Kernel32) 
	{
		g_CallGate._VirtualAlloc = fnVirtualAlloc(resolved_functions(g_CallGate.Kernel32, HashVirtualAlloc));
		g_CallGate._VirtualAllocEx = fnVirtualAllocEx(resolved_functions(g_CallGate.Kernel32, HashVirtualAllocEx));
		g_CallGate._VirtualProtect = fnVirtualProtect(resolved_functions(g_CallGate.Kernel32, HashVirtualProtect));
		g_CallGate._CreateThread = fnCreateThread(resolved_functions(g_CallGate.Kernel32, HashCreateThread));
		g_CallGate._CreateRemoteThread = fnCreateRemoteThread(resolved_functions(g_CallGate.Kernel32, HashCreateRemoteThrad));
		g_CallGate._VirtualFree = fnVirtualFree(resolved_functions(g_CallGate.Kernel32, HashVirtualFree));
	}

	if ((g_CallGate.Ntdll = GetModuleHandleW(L"Ntdll.DLL")) == ERROR) 
	{
		g_CallGate.Ntdll = LoadLibraryW(L"Ntdll.DLL");
	}
	if (g_CallGate.Ntdll) 
	{
		g_CallGate._RtlMoveMemory = fnRtlMoveMemory(resolved_functions(g_CallGate.Ntdll, HashRtlMoveMemory));
	}
}

HMODULE obfuscation::get_proc_address(HMODULE arg_module_base, DWORD arg_hash, DWORD arg_data_directory)
{
	PIMAGE_DOS_HEADER image_dos_header = PIMAGE_DOS_HEADER(arg_module_base);
	if (image_dos_header->e_magic == IMAGE_DOS_SIGNATURE) {
		PIMAGE_NT_HEADERS nt_headers = PIMAGE_NT_HEADERS(offset_to_pointer(arg_module_base, image_dos_header->e_lfanew));
		if (nt_headers->Signature == IMAGE_NT_SIGNATURE) {
			if (nt_headers->OptionalHeader.DataDirectory[arg_data_directory].VirtualAddress && arg_data_directory < nt_headers->OptionalHeader.NumberOfRvaAndSizes) {
				PIMAGE_EXPORT_DIRECTORY image_export = PIMAGE_EXPORT_DIRECTORY(PBYTE(offset_to_pointer(arg_module_base, nt_headers->OptionalHeader.DataDirectory[arg_data_directory].VirtualAddress)));
				if (image_export != ERROR) {
					PDWORD address_of_names = PDWORD(offset_to_pointer(arg_module_base, image_export->AddressOfNames));
					for (DWORD n = NULL; n < image_export->NumberOfNames; ++n) {
						LPSTR hashed_returned_names = LPSTR(offset_to_pointer(arg_module_base, address_of_names[n]));
						if (encoder::api_call_hashed(hashed_returned_names) == arg_hash)
						{
							PDWORD address_of_function = PDWORD(offset_to_pointer(arg_module_base, image_export->AddressOfFunctions));
							PWORD address_of_ordinal = PWORD(offset_to_pointer(arg_module_base, image_export->AddressOfNameOrdinals));
							return HMODULE(offset_to_pointer(arg_module_base, address_of_function[address_of_ordinal[n]]));
						}
					}
				}
			}
		}
	}
	return ERROR;
}

UINT encoder::api_call_hashed(PCHAR arg_input)
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

HMODULE obfuscation::resolved_functions(HMODULE arg_module_base, DWORD arg_hash) {
	return get_proc_address(arg_module_base, arg_hash, 0);
}