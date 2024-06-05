#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <memory>
#include <string_view>
#include <cstdint>
#include <vector>
#include "Ioctl.h"
#include <thread>

typedef struct _NULL_MEMORY
{
	void* buffer_address;
	UINT_PTR address;
	ULONGLONG size;
	ULONG pid;
	BOOLEAN write;
	BOOLEAN read;
	BOOLEAN req_base;
	void* output;
	const char* module_name;
	ULONG64 base_address;
}NULL_MEMORY;

uintptr_t base_address = 0;
std::uint32_t process_id = 0;

template<typename ... Arg>
uint64_t call_hook(const Arg ... args)
{
	void* hooked_func = GetProcAddress(LoadLibrary("win32u.dll"), "NtQueryCompositionSurfaceStatistics");

	if (hooked_func == nullptr) {
		throw std::runtime_error("Failed to load function from win32u.dll");
	}

	auto func = static_cast<uint64_t(_stdcall*)(Arg...)>(hooked_func);

	try {
		return func(args...);
	}
	catch (const std::exception& e) {
		// Exception occurred, handle it appropriately
		// You can print an error message or rethrow the exception
		// For example: std::cerr << "Error: " << e.what() << std::endl;
		// Or: throw;
	}

	// Handle the case when an error occurs
	// Return an appropriate error code/value
	// For example: return 0;
}

struct HandleDisposer
{
	using pointer = HANDLE;
	void operator()(HANDLE handle) const
	{
		if (handle != NULL || handle != INVALID_HANDLE_VALUE)
		{
			CloseHandle(handle);
		}
	}
};

using unique_handle = std::unique_ptr<HANDLE, HandleDisposer>;

std::uint32_t get_process_id(std::string_view process_name)
{
	PROCESSENTRY32 processentry;
	const unique_handle snapshot_handle(CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL));

	if (snapshot_handle.get() == INVALID_HANDLE_VALUE)
		return NULL;

	processentry.dwSize = sizeof(MODULEENTRY32);

	while (Process32Next(snapshot_handle.get(), &processentry) == TRUE)
	{
		if (process_name.compare(processentry.szExeFile) == NULL)
		{
			return processentry.th32ProcessID;
		}
	}
	return NULL;
}


#include <stdexcept> // For exception handling

ULONG64 get_module_base_address(const char* module_name)
{
	try {
		NULL_MEMORY instructions = { 0 };
		instructions.pid = process_id;
		instructions.req_base = TRUE;
		instructions.read = FALSE;
		instructions.write = FALSE;
		instructions.module_name = module_name;
		call_hook(&instructions);

		if (instructions.base_address == NULL) {
			// Error occurred, handle it appropriately
			throw std::runtime_error("Error retrieving module base address");
		}

		ULONG64 base = instructions.base_address;
		return base;
	}
	catch (const std::exception& e) {
		// Exception occurred, handle it appropriately
		// You can print an error message or return an error code/value
		// For example: std::cerr << "Error: " << e.what() << std::endl;
		// Or: return -1;
	}

	// Handle the case when an error occurs
	// Return an appropriate error code/value
	// For example: return -1;
}

template <class T>
T Read(UINT_PTR read_address)
{
	T response{};
	NULL_MEMORY instructions;
	instructions.pid = process_id;
	instructions.size = sizeof(T);
	instructions.address = read_address;
	instructions.read = TRUE;
	instructions.write = FALSE;
	instructions.req_base = FALSE;
	instructions.output = &response;
	call_hook(&instructions);

	return response;
}

bool write_memory(UINT_PTR write_address, UINT_PTR source_address, SIZE_T write_size)
{
	NULL_MEMORY instructions;
	instructions.address = write_address;
	instructions.pid = process_id;
	instructions.write = TRUE;
	instructions.read = FALSE;
	instructions.req_base = FALSE;
	instructions.buffer_address = (void*)source_address;
	instructions.size = write_size;

	call_hook(&instructions);

	return true;
}

template<typename S>
bool write(UINT_PTR write_address, const S& value)
{
	return write_memory(write_address, (UINT_PTR)&value, sizeof(S));
}

bool write_kernel_int(UINT_PTR write_address, const int value)
{
	write(write_address, value);

	return true;
}



bool TerminateProcessByName(const char* processName)
{
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (snapshot != INVALID_HANDLE_VALUE)
	{
		PROCESSENTRY32 processEntry;
		processEntry.dwSize = sizeof(PROCESSENTRY32);

		if (Process32First(snapshot, &processEntry))
		{
			do {
				if (_stricmp(processEntry.szExeFile, processName) == 0) {
					HANDLE processHandle = OpenProcess(PROCESS_TERMINATE, FALSE, processEntry.th32ProcessID);
					if (processHandle != NULL)
					{
						if (TerminateProcess(processHandle, 0))
						{
							CloseHandle(processHandle);
							CloseHandle(snapshot);
							std::cout << "Plutonium Terminated Successfully" << std::endl;
							return true;
						}
						else
						{
							CloseHandle(processHandle);
							CloseHandle(snapshot);
							return false;
						}
					}
					else
					{
						CloseHandle(snapshot);
						return false;
					}
				}
			} while (Process32Next(snapshot, &processEntry));
		}
	}

	CloseHandle(snapshot);
	return false;
}

bool IsProcessRunning(const char* processName)
{
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (snapshot != INVALID_HANDLE_VALUE)
	{
		PROCESSENTRY32 processEntry;
		processEntry.dwSize = sizeof(PROCESSENTRY32);

		if (Process32First(snapshot, &processEntry))
		{
			do
			{
				if (strcmp(processEntry.szExeFile, processName) == 0)
				{
					CloseHandle(snapshot);
					return true;
				}
			} while (Process32Next(snapshot, &processEntry));
		}
	}
	CloseHandle(snapshot);
	return false;
}
void ProcessCheckThread(const char* processName)
{

	std::cout << "ProcessCheckThread Called..." << std::endl;
	//Initialized and now waiting for program to open
	while (!isRunning)
	{
		bool processIsRunning = IsProcessRunning(processName);

		if (processIsRunning)
		{
			isRunning = true;
			MessageBox(nullptr, "Setup not finished.. Terminating", "Fatal Error", MB_ICONERROR | MB_OK);
			Sleep(2000);
			exit(0);
			// Perform additional actions if the process is running
		}
		else
		{
			std::cout << "Checking security..." << std::endl;
			return;
			// Perform additional actions if the process is not running
		}

		// Delay between each check
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}


}

