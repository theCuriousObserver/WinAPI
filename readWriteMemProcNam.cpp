// Reference: https://stackoverflow.com/questions/865152/how-can-i-get-a-process-handle-by-its-name-in-c

// ------------------------------- C++ program to read and write memory of a file using process name -------------------------------

#include <iostream>
#include <windows.h>
#include <tlhelp32.h>

using namespace std;

int main()

{
    int value;
    int newValue = 1000;

    DWORD address = 0x29270000;

    PROCESSENTRY32 entry;
    entry.dwSize = sizeof(PROCESSENTRY32);

    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

    if (Process32First(snapshot, &entry) == TRUE)
    {
        while (Process32Next(snapshot, &entry) == TRUE)
        {
            if (stricmp((const char *)entry.szExeFile, "notepad.exe") == 0)
            {
                HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, entry.th32ProcessID);

                if (!hProcess)
                {

                    cerr << "Cannot open process." << endl;
                }
                else
                {
                    int isReadSuccessful = ReadProcessMemory(hProcess, (LPVOID)address, &value, sizeof(value), 0);

                    if (isReadSuccessful > 0)
                    {

                        clog << "Process memory read." << endl;
                    }
                    else
                    {

                        cerr << "Cannot read process memory." << endl;
                    }

                    int isWriteSuccessful = WriteProcessMemory(hProcess, (LPVOID)address, &newValue, (DWORD)sizeof(newValue), NULL);

                    if (isWriteSuccessful > 0)
                    {

                        clog << "Process memory written." << endl;
                    }
                    else
                    {

                        cerr << "Cannot write process memory." << endl;
                    }

                    CloseHandle(hProcess);
                }
            }
        }
    }
}
