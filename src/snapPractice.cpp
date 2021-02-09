/** Objective, gather process snap and output to console
 * 
 */

#include<iostream>
#include<windows.h>
#include<tlhelp32.h>
#include<tchar.h>

// class Snap {

//     public:
//         Snap();
//         ~Snap();

//         WINBOOL checkSnap();

//     private:
//         // HANDLE procSnapshot{ CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0) };

//         void Snap::setSnapSize();
//         void Snap::closeSnap();

// };

void enterToContinue();

enum Operation {
    print_all,
    filter_name
};

int main(int argc, char *argv[]) {

    Operation opID{ filter_name };

    HANDLE procSnapshot{ CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0) };
    if (procSnapshot == INVALID_HANDLE_VALUE) {
        std::cout << "HANDLE FAILED to initialize" << std::endl;
        enterToContinue();
        return EXIT_FAILURE;
    }

    PROCESSENTRY32 procEntry{ dwSize: sizeof(PROCESSENTRY32) };

    if (!Process32First(procSnapshot, &procEntry)) {
        std::cout << "Process32First returnd FALSE" << std::endl;
        CloseHandle(procSnapshot);
        enterToContinue();
        return EXIT_FAILURE;
    }

    if (opID == print_all) {
        do {

            _tprintf( TEXT("\n\n======================================================") );
            _tprintf( TEXT("\nProcess Name: %s"), procEntry.szExeFile );
            _tprintf( TEXT("\n\n======================================================") );
            _tprintf( TEXT("\n  Process ID          = 0x%08X" ), procEntry.th32ProcessID );
            _tprintf( TEXT("\n  Parent Process ID   = 0x%08X" ), procEntry.th32ParentProcessID );
            _tprintf( TEXT("\n  Module ID           = %d" ), procEntry.th32ModuleID );
            _tprintf( TEXT("\n  Flags               = %d" ), procEntry.dwFlags );
            _tprintf( TEXT("\n  Process Size        = %d" ), procEntry.dwSize );
            _tprintf( TEXT("\n  Thread Count        = %d" ), procEntry.cntThreads );
            _tprintf( TEXT("\n  Usage Count         = %d\n" ), procEntry.cntUsage );

        } while( Process32Next(procSnapshot, &procEntry) );
    }

    if (opID == filter_name) {
        // const wchar_t* procName{ L"ac_client.exe" };
        // const wchar_t* procName{ L"ac_client.exe" };
        const wchar_t* procName = L"ac_client.exe";

        // std::cout << "(WCHAR)procName = " << (wchar_t)procName << std::endl;
        // std::cout << "procName = " << procName << std::endl;
        // std::cout << "*procName = " << (wchar_t)*procName << std::endl;
        // std::cout << "*procName = " << *procName << std::endl;
        // std::cout << "&procName = " << &procName << std::endl;
        
        do {
            // if (!_wcsicmp((wchar_t*)procEntry.szExeFile, procName)) {
            if ((wchar_t*)procEntry.szExeFile == procName) {
                _tprintf( TEXT("\nProcess Found!\nDetails\n==================================================\n\n") );
                _tprintf( TEXT("\nProcess Name: %s"), procEntry.szExeFile );
                _tprintf( TEXT("\n\n======================================================") );
                _tprintf( TEXT("\n  Process ID          = 0x%08X" ), procEntry.th32ProcessID );
                _tprintf( TEXT("\n  Parent Process ID   = 0x%08X" ), procEntry.th32ParentProcessID );
                _tprintf( TEXT("\n  Module ID           = %d" ), procEntry.th32ModuleID );
                _tprintf( TEXT("\n  Flags               = %d" ), procEntry.dwFlags );
                _tprintf( TEXT("\n  Process Size        = %d" ), procEntry.dwSize );
                _tprintf( TEXT("\n  Thread Count        = %d" ), procEntry.cntThreads );
                _tprintf( TEXT("\n  Usage Count         = %d\n" ), procEntry.cntUsage );

                break;
            }
        } while( Process32Next(procSnapshot, &procEntry) );
    }
    
    CloseHandle(procSnapshot);
    enterToContinue();
    return EXIT_SUCCESS;
}

void enterToContinue() {
    std::cout << "Press ENTER to continue" << std::endl;
    getchar();
}


// Snap::Snap() { }
// Snap::~Snap() {
//     closeSnap();
// }

// set structure size
// void Snap::setSnapSize() {
//     Snap::procSnapshot.dwSize = sizeof(procSnapshot);
// }

// Checks state of private snap
// WINBOOL Snap::checkSnap() {
//     if (procSnapshot == INVALID_HANDLE_VALUE) {
//         std::cout << "Handle invalid" << std::endl;
//         return{ FALSE };
//     } else {
//         return{ TRUE };
//     }
// }

// void Snap::closeSnap() {
//     if (procSnapshot != INVALID_HANDLE_VALUE)
//     {
//         CloseHandle(procSnapshot);
//         std::cout << "Handle closed successfully" << std::endl;
//     } else {
//         std::cout << "Handle is already closed" << std::endl;
//     }
// }
