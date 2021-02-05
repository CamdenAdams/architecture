
#include<iostream>
#include"p.h"

using namespace std;

int main() {

    cout << "press any key" << endl;
    getchar();
    cout << "explorer.exe processId: " << getProcessID(L"explorer.exe") << endl;
    getchar();


    return EXIT_SUCCESS;
}

DWORD getProcessID(const wchar_t* processName) {

    /** HANDLE WINAPI CreateToolhelp32Snapshot(DWORD dwFlags,DWORD th32ProcessID);
     * https://docs.microsoft.com/en-us/windows/win32/api/tlhelp32/nf-tlhelp32-createtoolhelp32snapshot
     * @param DWORD dwFlags: indicates portion of the systems to be included in the snapshot
     *      value = TH32CS_SNAPPROCESS - requests all processes in the system in the snapshot
     * @param DWORD th32ProcessID: The process identifier of the process to be included in the snapshot. This parameter can be zero to indicate the current process
     * @return success > returns open object handle to snapshot : failure > returns INVALID_HANDLE_VALUE
     */
    HANDLE hProcSnap{ CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0) };
    if (hProcSnap != INVALID_HANDLE_VALUE)
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
                /** int _wcsicmp(const char *string1, const char *string2)
                 * https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/stricmp-wcsicmp-mbsicmp-stricmp-l-wcsicmp-l-mbsicmp-l?view=msvc-160
                 * @return 0 if identicle, less than 0 if string1 < string2, greater than 0 if string1 > string2
                 */
                if (!_wcsicmp(procEntry.szExeFile, processName)) // case insensitive comparison of process name from procEntry and function argument - Using over: if (procEntry.szExeFile == processName)
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