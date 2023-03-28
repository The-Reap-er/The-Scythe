#include "../headers/require.h"
#include "../headers/anti_analysis.h"

bool environment::virtualization::vbox()
{
    HANDLE handle = CreateFile("\\\\.\\VBoxMiniRdrDN", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (handle != INVALID_HANDLE_VALUE) 
    { 
        CloseHandle(handle); 
        return true; 
    }
    return false;
}

bool environment::virtualization::vmware()
{
    HKEY hKey = 0; DWORD dwType = REG_SZ; char buf[255] = { 0 }; DWORD dwBufSize = sizeof(buf);
    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\VMware, Inc.\\VMware Tools", 0, KEY_QUERY_VALUE, &hKey) == ERROR_SUCCESS) 
    { 
        return true; 
    }
    return false;
}

bool environment::virtualization::vmware_tools()
{
    HKEY handle_vm_tool_key;
    char* vmtool_buffer;
    DWORD size = 256;
    DWORD type;
    vmtool_buffer = (char*)malloc(sizeof(char) * size);

    LSTATUS registry_open_status = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SYSTEM\\ControlSet001\\Services\\VMTools", 0, KEY_READ, &handle_vm_tool_key);
    if (registry_open_status != ERROR_SUCCESS) 
    {
        free(vmtool_buffer);
        return false;
    }

    DWORD registry_query_status = RegQueryValueExA(handle_vm_tool_key, "ImagePath", NULL, &type, (LPBYTE)vmtool_buffer, &size);
    while (registry_query_status == ERROR_MORE_DATA) 
    {
        size += 256;
        vmtool_buffer = (char*)realloc(vmtool_buffer, size);
        registry_query_status = RegQueryValueExA(handle_vm_tool_key, "0", NULL, &type, (LPBYTE)vmtool_buffer, &size);
    }

    if (registry_query_status == ERROR_SUCCESS) 
    {
        char* lower_case_value = CharLowerA((char*)vmtool_buffer);
        char* result = strstr(lower_case_value, "vmtoolsd.exe");
        if (result) 
        {
            return true;
        }
        else 
        {
            return false;
        }
    }
    RegCloseKey(handle_vm_tool_key);
    free(vmtool_buffer);
    return false;
}

bool environment::virtualization::tsc_register()
{

#if _WIN64 
    UINT64 time1 = __rdtsc();
    UINT64 time2 = __rdtsc();
    if (time2 - time1 > 500) {
        return true;
    }
#else 
    unsigned int time1 = 0;
    unsigned int time2 = 0;
    __asm
    {
        RDTSC
        MOV time1, EAX
        RDTSC
        MOV time2, EAX

    }
    if (time2 - time1 > 500) {
        return true;
    }
    return false;
#endif
}

bool environment::virtualization::vmware_drivers()
{
    LPVOID drivers[1024];
    DWORD pcb_needed;
    int driver_list;

    if (EnumDeviceDrivers(drivers, sizeof(drivers), &pcb_needed) && pcb_needed < sizeof(drivers)) {

        CHAR driver_name[1024];
        driver_list = pcb_needed / sizeof(drivers[0]);
        for (int i = 0; i < driver_list; i++) 
        {
            GetDeviceDriverBaseNameA(drivers[i], driver_name, sizeof(driver_name) / sizeof(driver_name[0]));
            if (strcmp(driver_name, "vmmouse.sys") == 0 || strcmp(driver_name, "vmmemctl.sys") == 0) 
            {
                return true;
            }
        }
    }
    else 
    {
        return false;
    }

    return false;
}

bool environment::virtualization::vmware_services()
{
    SC_HANDLE hSCManager = ::OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
    if (hSCManager == NULL) 
    {
        if (GetLastError() == 5) 
        {
            return false;
        }
        return false;
    }

    SC_HANDLE hVMPhysicalDiskService = OpenService(hSCManager, "VMware Physical Disk Helper Service", SERVICE_ALL_ACCESS);
    SC_HANDLE hVMSnapshotService = OpenService(hSCManager, "vmss", SERVICE_ALL_ACCESS);

    if ((hVMPhysicalDiskService == NULL) && (hVMSnapshotService == NULL)) 
    {
        return false;
    }

    CloseServiceHandle(hSCManager);
    CloseServiceHandle(hVMPhysicalDiskService);
    CloseServiceHandle(hVMSnapshotService);
    return true;
}

BOOL environment::utils::self_delete()
{

    char file_path[MAX_PATH], command[MAX_PATH];

    if ((GetModuleFileName(0, file_path, MAX_PATH) != 0) && (GetShortPathName(file_path, file_path, MAX_PATH) != 0))
    {
        lstrcpy(command, "/c del "); lstrcat(command, file_path); lstrcat(command, " >> NUL");
        if ((GetEnvironmentVariable("ComSpec", file_path, MAX_PATH) != 0) && ((INT)ShellExecute(0, 0, file_path, command, 0, SW_HIDE) > 32))
        {
            return TRUE;
        }
    }

    return FALSE;
}

bool environment::anti_debugging::debug_port()
{
    HMODULE ntdll_handle = LoadLibraryA("ntdll.dll");

    if (ntdll_handle == NULL)
        return NULL;


    auto NtQueryInfoProcess = (pNtQueryInformationProcess)(GetProcAddress(ntdll_handle, "NtQueryInformationProcess"));

    // ProcessDebugPort
    const int process_dbg_port = 7;

    // Other Vars
    NTSTATUS status;

    DWORD process_information_length = sizeof(ULONG) * 2;
    DWORD64 is_remote_present = 0;

    status = NtQueryInfoProcess(GetCurrentProcess(), process_dbg_port, &is_remote_present, process_information_length, NULL);
    if (status == 0x00000000 && is_remote_present != 0)
        return true;
    else
        return false;
}

bool environment::anti_debugging::debug_object()
{
    HMODULE ntdll_handle = LoadLibraryA("ntdll.dll");
    const int process_debug_object_handle = 0x1e;
    auto NtQueryInfoProcess = (pNtQueryInformationProcess)(GetProcAddress(ntdll_handle, "NtQueryInformationProcess"));

    NTSTATUS status;
    HANDLE handle_debug_object = NULL;

    DWORD process_information_length = sizeof(ULONG) * 2;
    DWORD64 is_remote_present = 0;

    status = NtQueryInfoProcess(GetCurrentProcess(), process_debug_object_handle, &handle_debug_object, process_information_length, NULL);

    if (status != (NTSTATUS)0xC0000353L)
        return true;

    if (handle_debug_object != NULL)
        return true;

    status = NtQueryInfoProcess(GetCurrentProcess(), process_debug_object_handle, &handle_debug_object, process_information_length, (PULONG)&handle_debug_object);
    if (status != (NTSTATUS)0xC0000353L)
        return true;

    if (handle_debug_object == NULL)
        return true;

    if ((ULONG)(ULONG_PTR)handle_debug_object != process_information_length)
        return true;

    return false;
}

bool environment::anti_debugging::debug_inherit()
{
    HMODULE ntdll_handle = LoadLibraryA("ntdll.dll");

    const int process_debug_flags = 0x1f;

    auto NtQueryInfoProcess = (pNtQueryInformationProcess)(GetProcAddress(ntdll_handle, "NtQueryInformationProcess"));

    NTSTATUS status;
    DWORD no_debug_inherit = 0;

    status = NtQueryInfoProcess(GetCurrentProcess(), process_debug_flags, &no_debug_inherit, sizeof(DWORD), NULL);
    if (status == 0x00000000 && no_debug_inherit == 0)
        return true;
    else
        return false;
}

bool environment::anti_debugging::info_class()
{
    HMODULE ntdll_handle = LoadLibraryA("ntdll.dll");

    const int thread_hide_from_debugger = 0x11;

    auto NtSetInformationThread = (pNtSetInformationThread)(GetProcAddress(ntdll_handle, "NtSetInformationThread"));
    auto NtQueryInformationThread = (pNtQueryInformationThread)(GetProcAddress(ntdll_handle, "NtQueryInformationThread"));

    NTSTATUS status;
    bool os_check = IsWindowsVistaOrGreater();
    bool is_thread_hidden = false;

    status = NtSetInformationThread(GetCurrentThread(), thread_hide_from_debugger, &is_thread_hidden, 12345);
    if (status == 0)
    {
        return true;
    }

    status = NtSetInformationThread((HANDLE)0xFFFF, thread_hide_from_debugger, NULL, 0);
    if (status == 0)
    {
        return true;
    }

    status = NtSetInformationThread(GetCurrentThread(), thread_hide_from_debugger, NULL, 0);
    if (status == 0)
    {
        if (os_check)
        {
            status = NtQueryInformationThread(GetCurrentThread(), thread_hide_from_debugger, &is_thread_hidden, sizeof(BOOL), NULL);
            if (status == 0)
            {
                return is_thread_hidden ? false : true;
            }
        }
    }
    else
    {
        return true;
    }

    return false;
}

bool environment::anti_debugging::remote_debuger()
{
    BOOL result = false;
    CheckRemoteDebuggerPresent(GetCurrentProcess(), &result);
    if (result)
        return true;
    else
        return false;
}

bool environment::anti_debugging::debuger_present()
{
    return IsDebuggerPresent();
}

bool environment::anti_debugging::being_debuged()
{
    PPEB process_environment_block = (PPEB)__readgsqword(0x60);

    if (process_environment_block->BeingDebugged == 1)
        return true;
    else
        return false;
}