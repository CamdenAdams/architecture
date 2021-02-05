#pragma once // what does this pre-processor directive do?

#include<windows.h>
#include<tlhelp32.h>
#include<vector>

DWORD getProcessID(const wchar_t* processName);