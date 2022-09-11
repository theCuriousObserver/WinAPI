#include <iostream>

#include <windows.h>

using namespace std;

int main()

{
    int value;
    int newValue = 500;

    HWND hWnd = FindWindow(TEXT("Notepad"), NULL);

    if (hWnd == 0)
    {

        cerr << "Cannot find window." << endl;
    }
    else
    {

        DWORD pId;

        DWORD address = 0x0A240000;

        GetWindowThreadProcessId(hWnd, &pId);

        HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pId);

        if (!hProc)
        {

            cerr << "Cannot open process." << endl;
        }
        else
        {
            int isReadSuccessful = ReadProcessMemory(hProc, (LPVOID)address, &value, sizeof(value), 0);

            if (isReadSuccessful > 0)
            {

                clog << "Process memory read." << endl;
            }
            else
            {

                cerr << "Cannot read process memory." << endl;
            }

            int isWriteSuccessful = WriteProcessMemory(hProc, (LPVOID)address, &newValue, (DWORD)sizeof(newValue), NULL);

            if (isWriteSuccessful > 0)
            {

                clog << "Process memory written." << endl;
            }
            else
            {

                cerr << "Cannot write process memory." << endl;
            }

            CloseHandle(hProc);
        }
    }

    return 0;
}
