#pragma once // what does this pre-processor directive do?


#include<windows.h>
#include<tlhelp32.h>
#include<vector>
#include<iostream>

#include<stdint.h>

// DWORD getProcessID(const wchar_t* processName);

// uintptr_t getModuleBaseAddress(DWORD processID, const wchar_t* moduleName);

// uintptr_t findDMAAddr(HANDLE hProcess, uintptr_t basePtr, std::vector<unsigned int> offsets);


/** 
 * char - supports UTF-8 encoding - 8 bit type
 * wchar_t - supports UTF-16LE encoding - 16-bit type
 *  - UTF-16LE is the default character set for Windows operating systems - since we're working with the Windows api, makes sense we would use it
 *  - https://docs.microsoft.com/en-us/cpp/cpp/char-wchar-t-char16-t-char32-t?view=msvc-160
 * 
 */ 

DWORD getProcessID(const wchar_t* processName) {

    /** HANDLE WINAPI CreateToolhelp32Snapshot(DWORD dwFlags,DWORD th32ProcessID);
     * https://docs.microsoft.com/en-us/windows/win32/api/tlhelp32/nf-tlhelp32-createtoolhelp32snapshot
     * @param DWORD dwFlags: indicates portion of the systems to be included in the snapshot
     *      value = TH32CS_SNAPPROCESS - requests all processes in the system in the snapshot
     * @param DWORD th32ProcessID: The process identifier of the process to be included in the snapshot. This parameter can be zero to indicate the current process
     * @return success > returns open object handle to snapshot : failure > returns INVALID_HANDLE_VALUE
     */
    HANDLE hProcSnap{ CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0) };
    if (hProcSnap == INVALID_HANDLE_VALUE)
    {
        std::cout << "hProcSnap == INVALID_HANDLE_VALUE && GetLastError() == " << GetLastError() << std::endl;
        getchar();
        return 0;
    }
    else
    {
        // PROCESSENTRY32 Struct - peek (alt+f12) tlhelp32.h (line 80)
        // The size of the structure, in bytes. Before calling the Process32First function, set this member to sizeof(PROCESSENTRY32). If you do not initialize dwSize, Process32First fails.
        PROCESSENTRY32 procEntry{ dwSize: sizeof(PROCESSENTRY32) };     // I do not think this works
        // PROCESSENTRY32 procEntry{ };
        // procEntry.dwSize = sizeof(procEntry);

        /** WINBOOL WINAPI Process32First(HANDLE hSnapshot,LPPROCESSENTRY32W lppe);
         * https://docs.microsoft.com/en-us/windows/win32/api/tlhelp32/nf-tlhelp32-process32first
         * @return TRUE if the first entry of the process list has been copied to the buffer, otherwise FALSE
         */
        if (Process32First(hProcSnap, &procEntry)) {

            do
            {
                const wchar_t* currentProcEntryExeFile{ (wchar_t *)procEntry.szExeFile };

                /** int _wcsicmp(const char *string1, const char *string2)
                 * https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/stricmp-wcsicmp-mbsicmp-stricmp-l-wcsicmp-l-mbsicmp-l?view=msvc-160
                 * @return 0 if identicle, less than 0 if string1 < string2, greater than 0 if string1 > string2
                 */
                // if (!_wcsicmp(procEntry.szExeFile, processName)) // case insensitive comparison of process name from procEntry and function argument - Using over: if (procEntry.szExeFile == processName)
                if (!_wcsicmp(currentProcEntryExeFile, processName))
                {
                    DWORD procID{ procEntry.th32ProcessID };
                    CloseHandle(hProcSnap);
                    return procID;
                }
            } while (Process32Next(hProcSnap, &procEntry));     // Process32Next() is very similar to Process32First(), simply copies the next process entry to the buffer instead of the first
        }
    }
    
    CloseHandle(hProcSnap);
    return 0;
}

uintptr_t getModuleBaseAddress(DWORD processID, const wchar_t* moduleName) {
    HANDLE hModuleSnap{ CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, processID) };
    if (hModuleSnap != INVALID_HANDLE_VALUE)
    {
        MODULEENTRY32 moduleEntry{ dwSize: sizeof(MODULEENTRY32) };
        // MODULEENTRY32 moduleEntry{ };
        // moduleEntry.dwSize = sizeof(moduleEntry);

        if (Module32First(hModuleSnap, &moduleEntry))
        {
            do
            {
                const wchar_t* currentModuleEntryExeFile{ (wchar_t *)moduleEntry.szModule };
                // if... !_wcsicmp(hModuleSnap.szModule, moduleName) == 0 : _wscicmp() == 0 is exact match
                if (!_wcsicmp(currentModuleEntryExeFile, moduleName))
                {
                    uintptr_t moduleBaseAddress{ (uintptr_t)moduleEntry.modBaseAddr };
                    CloseHandle(hModuleSnap);
                    return moduleBaseAddress;
                }
            } while (Module32Next(hModuleSnap, &moduleEntry));
        }
    }

    CloseHandle(hModuleSnap);
    return 0;
}

/** findDMAAddr - Find dynamic memory allocation address
 * 
 * @param hProcess - handle to process
 * @param basePtr - client base address
 * @param offsets - offsets of basePtr to important traits
 * @return not sure
 */
uintptr_t findDMAAddr(HANDLE hProcess, uintptr_t basePtr, std::vector<unsigned int> offsets) {
    uintptr_t address{ basePtr };
    for (size_t i = 0; i < offsets.size(); i++)
    {
        ReadProcessMemory(hProcess, (LPCVOID)address, &address, sizeof(address), NULL);
        address += offsets[i];
    }
    return address;
}