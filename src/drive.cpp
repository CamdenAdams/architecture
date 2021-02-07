
#include"p.h"

// using namespace std;

int main(int argc, char *argv[]) {

    // resolved from pointer chain exercise
    // 02A1A5C0 = value = 14

    // basePtr -> address + offset(n) = address

    // 1. basePtr -> address + 0x0 = 02A1A5C0
    //     02A1A5C0 - 0x0 = 02A1A5C0
    //     address = 02A1A5C0
    //     basePtr = 02A11834 [found via hex scan for 02A1A5C0]
    //         02A11834 -> 02A1A5C0 + 0x0 = 02A1A5C0

    // 2. 02A1A7F4 -> 02A11820 + 0x14 = 02A11834

    // 3. basePtr -> address + offset(n) = 02A1A7F4
    // ac_client.exe+10F4F4 -> 02A1A470 + 0x384 = 02A1A7F4
    //     02A1A7F4 - 0x384 = 02A1A470
    //     static base = ac_client.exe+10F4F4 = 0x0050F4F4

    // static base + offset1 + offset2 + offset3 = startAddress
    // ac_client.exe+10F4F4 (0x0050F4F4) + 0x0384 + 0x14 + 0x0 = 02A1A5C0
    // [[[[ac_client.exe+10F4F4] + 0x384] + 0x14] + 0x0] = 02A1A5C0

    uintptr_t relativeOffsetToPlayerBase{ 0x010F4F4 };

    // unsigned int vector containing offsets to target dynamic memory address
    std::vector<unsigned int> offsetsToCurrentAmmo{ 0x384, 0x14, 0x0 };

    // get processID
    // L"ac_client.exe" returns a (pointer)L"ac_client.exe"
    DWORD processID{ getProcessID(L"ac_client.exe") };
    if (!processID)
    {
        std::cout << "Process failed to initialize, processID = " << processID << std::endl;
        getchar();
        return EXIT_FAILURE;
    }
    else {
        // get module base address, base address of ac_client.exe
        uintptr_t moduleBaseAddress{ getModuleBaseAddress(processID, L"ac_client.exe") };

        // fetch process handle with least permissions required
        HANDLE hProcess{ OpenProcess(PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION, FALSE, processID) };
        if (hProcess == INVALID_HANDLE_VALUE)
        {
            std::cout << "HANDLE IS NULL: " << GetLastError() << std::endl;
            getchar();
            return EXIT_FAILURE;
        }

        // resolve base address of pointer chain - in respect to assault cube, this is base address to player object
        uintptr_t dynamicPtrToBaseAddress{ moduleBaseAddress + relativeOffsetToPlayerBase };
        std::cout << "dynamicPtrToBaseAddress = " << "0x" << std::hex << dynamicPtrToBaseAddress << std::endl;

        // resolve ammo pointer chain
        uintptr_t currentAmmoAddress{ findDMAAddr(hProcess, dynamicPtrToBaseAddress, offsetsToCurrentAmmo) };
        std::cout << "currentAmmoAddress = " << "0x" << std::hex << currentAmmoAddress << std::endl;

        int ammoValue{ 0 };
        ReadProcessMemory(hProcess, (LPCVOID)currentAmmoAddress, &ammoValue, sizeof(ammoValue), nullptr);
        std::cout << "ammoValue = " << std::dec << ammoValue << std::endl;

        int newAmmoValue{ 9999 };
        WriteProcessMemory(hProcess, (LPVOID)currentAmmoAddress, &newAmmoValue, sizeof(newAmmoValue), nullptr);

        ReadProcessMemory(hProcess, (LPCVOID)currentAmmoAddress, &ammoValue, sizeof(ammoValue), nullptr);
        std::cout << "ammoValue = " << std::dec << ammoValue << std::endl;

        std::cout << "Press enter to close" << std::endl;
        getchar();

        return EXIT_SUCCESS;

    }    
}