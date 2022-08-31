#include <iostream>
#include <Windows.h>
#include <string>
#include <TlHelp32.h>
using namespace std;

DWORD pid;
int target;

DWORD MyGetProcessId(LPCTSTR ProcessName)
{
    PROCESSENTRY32 pt;
    HANDLE hsnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    pt.dwSize = sizeof(PROCESSENTRY32);
    if (Process32First(hsnap, &pt))
    { // must call this first
        do
        {
            if (!lstrcmpi(pt.szExeFile, ProcessName))
            {
                CloseHandle(hsnap);
                return pt.th32ProcessID;
            }
        } while (Process32Next(hsnap, &pt));
    }
    CloseHandle(hsnap); // close handle on failure
    return 0;
}

int main()
{
    pid = MyGetProcessId(TEXT("VALORANT.exe")); // get process id
    HANDLE pHandle = OpenProcess(PROCESS_VM_READ, FALSE, pid);
    while (true)
    {
        cout << "Code Running" << endl;
    }
}