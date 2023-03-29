#pragma once

#include "Windows.h"

typedef int (WINAPI* fnMessageBoxW)(HWND, LPCTSTR, LPCTSTR, UINT);
#define HashMessageBoxW 1903425129

typedef HANDLE (WINAPI* fnCreateThread)(LPSECURITY_ATTRIBUTES, SIZE_T, LPTHREAD_START_ROUTINE, LPVOID, DWORD, LPDWORD);
#define HashCreateThread 154258924

typedef HANDLE (WINAPI* fnCreateRemoteThread)(HANDLE, LPSECURITY_ATTRIBUTES, SIZE_T, LPTHREAD_START_ROUTINE, LPVOID, DWORD, LPDWORD);
#define HashCreateRemoteThrad 10170233

typedef LPVOID (WINAPI* fnVirtualAlloc)(LPVOID, SIZE_T, DWORD, DWORD);
#define HashVirtualAlloc 1066648342

typedef LPVOID (WINAPI* fnVirtualAllocEx)(HANDLE, LPVOID, SIZE_T, DWORD, DWORD);
#define HashVirtualAllocEx 723109788

typedef BOOL (WINAPI* fnVirtualProtect)(LPVOID, SIZE_T, DWORD, PDWORD);
#define HashVirtualProtect 441587388

typedef BOOL(WINAPI* fnVirtualFree)(LPVOID, SIZE_T, DWORD);
#define HashVirtualFree 755756150

typedef VOID(WINAPI* fnRtlMoveMemory)(VOID UNALIGNED*, const VOID UNALIGNED*, SIZE_T);
#define HashRtlMoveMemory 1051400039

#define offset_to_pointer(Module, Pointer) PBYTE(PBYTE(Module) + DWORD(Pointer))

struct BASE 
{
	HMODULE User32;
	fnMessageBoxW _MessageBoxW;
	
	HMODULE Kernel32;
	fnCreateThread _CreateThread;
	fnCreateRemoteThread _CreateRemoteThread;
	fnVirtualAlloc _VirtualAlloc;
	fnVirtualAllocEx _VirtualAllocEx;
	fnVirtualProtect _VirtualProtect;
	fnVirtualFree _VirtualFree;

	HMODULE Ntdll;
	fnRtlMoveMemory _RtlMoveMemory;
};

namespace obfuscation {
	VOID	load();
	HMODULE get_proc_address(HMODULE arg_module_base, DWORD arg_hash, DWORD arg_data_directory);
	HMODULE resolved_functions(HMODULE arg_module_base, DWORD arg_hash);
}

namespace encoder {
	UINT api_call_hashed(PCHAR arg_input);
};

extern BASE g_CallGate;


