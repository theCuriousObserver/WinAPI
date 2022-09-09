#include <iostream>

#include <windows.h>

using namespace std;

int main()

{

    int newValue = 500;

    HWND hWnd = FindWindowA(0, "Notepad++");

    if (hWnd == 0)
    {

        cerr << "Cannot find window." << endl;
    }
    else
    {

        DWORD pId;

        GetWindowThreadProcessId(hWnd, &pId);

        HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pId);

        if (!hProc)
        {

            cerr << "Cannot open process." << endl;
        }
        else
        {

            int isSuccessful = WriteProcessMemory(hProc, (LPVOID)0x09CF0000, &newValue, (DWORD)sizeof(newValue), NULL);

            if (isSuccessful > 0)
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
