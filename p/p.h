#pragma once // what does this pre-processor directive do?


#include<windows.h>
#include<tlhelp32.h>
#include<vector>
#include<iostream>

#include<stdint.h>

DWORD getProcessID(const wchar_t* processName);

uintptr_t getModuleBaseAddress(DWORD processID, const wchar_t* moduleName);

uintptr_t findDMAAddr(HANDLE hProcess, uintptr_t basePtr, std::vector<unsigned int> offsets);
