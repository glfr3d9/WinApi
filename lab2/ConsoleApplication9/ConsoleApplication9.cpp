#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <Windows.h>
#include <cstring>

struct SharedData {
    int sch = 0;
    char mas[8];
};

HANDLE mutex;
HANDLE mapping;
using namespace std;

int main() {
    DWORD dwBytesWritten = 0;
    HANDLE hFile = CreateFile(TEXT("test1.txt"), GENERIC_WRITE | GENERIC_READ, FILE_SHARE_WRITE | FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    mapping = CreateFileMappingA(hFile, nullptr, PAGE_READWRITE, 0, sizeof(SharedData), "first1");
    unique_ptr<SharedData, decltype(&UnmapViewOfFile)> data((SharedData*)MapViewOfFile(mapping, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, 0), UnmapViewOfFile);
    mutex = OpenMutexA(MUTEX_ALL_ACCESS, TRUE, "first");
    while (mutex == NULL) {
        mutex = CreateMutexA(NULL, FALSE, "first");
    }
    cout << "mutex:" << mutex << endl;
    DWORD dwBytesToWrite = 13;
    thread user_input_thread([&] {
        WaitForSingleObject(mutex, INFINITE);
        for (int i = 0; i < 4; i++) {
            data->mas[data->sch] = '2';
            cout << "mas[" << data->sch << "]= " << data->mas[data->sch] << " ";
            WriteFile(hFile, (LPCVOID)data->mas[data->sch], dwBytesToWrite, &dwBytesWritten, NULL);
            Sleep(500);
            data->sch++;
        }
        ReleaseMutex(mutex);
        });
    user_input_thread.join();
    system("pause");
    CloseHandle(hFile);
}
