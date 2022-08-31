// Reference : https://chy.my.id/read-write-process-memory/

#include <iostream>
#include <Windows.h>
#include <string>
#include <TlHelp32.h>
using namespace std;

DWORD pid;
int target;

DWORD GetModuleBase(const wchar_t *ModuleName, DWORD ProcessId)
{
    // This structure contains lots of goodies about a module
    MODULEENTRY32 ModuleEntry = {0};
    // Grab a snapshot of all the modules in the specified process
    HANDLE SnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, ProcessId);

    if (!SnapShot)
        return NULL;

    // You have to initialize the size, otherwise it will not work
    ModuleEntry.dwSize = sizeof(ModuleEntry);

    // Get the first module in the process
    if (!Module32First(SnapShot, &ModuleEntry))
        return NULL;

    // do
    // {
    //     // Check if the module name matches the one we're looking for
    //     if (!wcscmp(ModuleEntry.szModule, ModuleName))
    //     {
    //         // If it does, close the snapshot handle and return the base address
    //         CloseHandle(SnapShot);
    //         return (DWORD)ModuleEntry.modBaseAddr;
    //     }
    //     // Grab the next module in the snapshot
    // } while (Module32Next(SnapShot, &ModuleEntry));

    // return the base address
    while (Module32Next(SnapShot, &ModuleEntry))
    {
        return (DWORD)ModuleEntry.modBaseAddr;
    }

    // We couldn't find the specified module, so return NULL
    CloseHandle(SnapShot);
    return NULL;
}
int main()
{
    HWND hWnd = FindWindowA(0, ("vgc.exe")); // Windows name program you want to target

    GetWindowThreadProcessId(hWnd, &pid);                      // This line used for get the ProcessID
    HANDLE pHandle = OpenProcess(PROCESS_VM_READ, FALSE, pid); // We use this to get a Object handle for our passing parameter in ReadProcessMemory function
    DWORD client = GetModuleBase(L"vgc.exe", pid);             // We find the base Address for process
    DWORD baseAddress = client + 0x1F3B6E0;                    // now we calculate our base address so it can form like this "exe" + 1F3B6E0

    DWORD address = 0;                                                             // we initialize a address variable for our final address later
    ReadProcessMemory(pHandle, (void *)baseAddress, &address, sizeof(address), 0); // we read the process memory address and save it to address variable we initialize before
    address += 0x170;                                                              // we add our offset to this final address so now this address variable value is pointer to read detected monster in radar "RF_Online.bin" + 1F3B6E0 with Offset 170

    // in this block we do loop for every 100ms to show update how much monster exist in our radar.
    while (true)
    {
        ReadProcessMemory(pHandle, (LPVOID)address, &target, sizeof(target), 0);
        cout << target << endl;
        Sleep(100);
        system("CLS");
    }
    system("Pause");
}