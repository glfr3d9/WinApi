#include <iostream>
#include <Windows.h>
#include <conio.h>

using namespace std;

#define pause() cout << "Press any key to continue..." << endl; _getch()

CRITICAL_SECTION cs;

DWORD WINAPI thread(LPVOID)
{
    int i, j;

    for (j = 0; j < 10; j++)
    {
        EnterCriticalSection(&cs);

        for (i = 0; i < 10; i++)
        {
            cout << j << ' ' << flush;
            Sleep(17);
        }
        cout << endl;

        LeaveCriticalSection(&cs);
    }

    return 0;
}

int main()
{
    int i, j;
    HANDLE hThread;
    DWORD IDThread;

    InitializeCriticalSection(&cs);

    hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread, NULL, 0, &IDThread);
    if (hThread == NULL)
    {
        cout << "Error of creating new thread..." << endl;
        pause();
        return GetLastError();
    }

    for (j = 0; j < 20; j++)
    {
        EnterCriticalSection(&cs);
        for (i = 0; i < 10; i++)
        {
            cout << j << ' ' << flush;
            Sleep(17);
        }

        cout << endl;
        LeaveCriticalSection(&cs);
    }

    WaitForSingleObject(hThread, 0xFFFFFFFF);
    DeleteCriticalSection(&cs);
    pause();
    return 0;
}
