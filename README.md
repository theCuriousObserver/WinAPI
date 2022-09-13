# WinAPI

This code is supposed to read and write memory address just like cheat engine.

We start by copying the code of readWriteMemProcNam.cpp into a code editor and replacing VALORANT.exe with our desired exe for which we want to test our API Calls on. 
Using Cheat Engine we find the base address of the exe file. We use this address in our code to read and write process memory. 

If we know the exact Window Title, we can also use readWriteMemoryWinNam.cpp to achieve the same result. We can use findWindowName.py in testfiles to find the name of active windows.

Consecutively, if the above steps are followed then the memory address should be read and overwritten by our code.
