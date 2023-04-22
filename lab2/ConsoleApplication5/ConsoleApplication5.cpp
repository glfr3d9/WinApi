#include <stdio.h> 
#include <windows.h> 

HANDLE hEvent1, hEvent2;
int a[5];
HANDLE hThr;
unsigned long uThrID;

void Thread(void* pParams)
{
    int i, num = 0;

    while (num < 20)
    {
        WaitForSingleObject(hEvent2, INFINITE);
        for (i = 0; i < 5; i++) a[i] = num;
        num++;
        SetEvent(hEvent1);
    }
}
int main(void)
{
    hEvent1 = CreateEvent(NULL, FALSE, TRUE, NULL);
    hEvent2 = CreateEvent(NULL, FALSE, FALSE, NULL);
    hThr = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Thread, NULL, 0, &uThrID);
    while (1)
    {
        WaitForSingleObject(hEvent1, INFINITE);
        Sleep(1000);
        printf("%d %d %d %d %d\n", a[0], a[1], a[2], a[3], a[4]);
        SetEvent(hEvent2);
    }
    return 0;
}
