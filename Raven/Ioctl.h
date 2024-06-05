#pragma once
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>
#include <windows.h>
#include <winnt.h>


inline std::atomic_bool isRunning{ false };

extern bool IsProcessRunning(const char* processName);

extern ULONG64 get_module_base_address(const char* module_name);

extern bool write_kernel_int(UINT_PTR write_address, const int value);
#endif

