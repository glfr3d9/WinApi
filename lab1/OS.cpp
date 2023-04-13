#include <windows.h>
#include <iostream>
#include <Lmcons.h>
#include <conio.h>
#include <windows.h>
#include <locale>

#define cout wcout
#define OSVERSIONINFO OSVERSIONINFOEX

using namespace std;
int main()
{
    setlocale(LC_ALL, "rus");
    cout.imbue(locale("rus_rus.1251"));
    WCHAR str[4096];
    DWORD sz = 4096;
    GetUserName(str, &sz);
    cout << "Имя пользователя: " << str << endl;
    GetComputerName(str, &sz);
    cout << "Имя компьютера: " << str << endl;
    GetSystemDirectory(str, 4096);
    cout << "Путь к системной папке: " << str << endl;
    GetWindowsDirectory(str, 4096);
    cout << "Пути к папке windows: " << str << endl;
    GetTempPath(4096, str);
    cout << "Путь к временной папке: " << str << endl;
    OSVERSIONINFO osversion;
    memset(&osversion, 0, sizeof(OSVERSIONINFO));
    osversion.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
    cout << "Версия системы (Основной номер. дополнительный. сборка)" << osversion.dwMajorVersion << "." << osversion.dwMinorVersion << "." << osversion.dwBuildNumber << endl;
    cout << "Платформа операционной системы: " << osversion.dwPlatformId << endl;

    cout << endl << "Системные метрики:" << endl;
    cout << "Разрешение экрана: " << GetSystemMetrics(0) << "x" << GetSystemMetrics(1) << endl;
    cout << "Ширина экрана: " << GetSystemMetrics(SM_CXSCREEN) << "; Высота экрана: " << GetSystemMetrics(SM_CYSCREEN) << endl;

    cout << endl << "Системные параметры: " << endl;
    unsigned int param;
    SystemParametersInfo(SPI_GETANIMATION, 0, &param, 0);
    cout << "Параметр анимации: " << param << endl; //Данные об анимации
    SystemParametersInfo(SPI_GETBEEP, 0, &param, 0);
    cout << "Признак разрешения звуковых сигналов: " << param << endl;

    cout << "\nИнформаци о времени: " << endl;
    SYSTEMTIME var1, var2;
    GetLocalTime(&var1);
    GetSystemTime(&var2);
    cout << "\nЛокальное время: дата " << var1.wDay << "." << var1.wMonth << L"." << var1.wYear << " время " << var1.wHour << ":" << var1.wMinute << endl;
    cout << "\nСистемное время: " << "дата " << var2.wDay << "." << var2.wMonth << "." << var2.wYear << " время " << var2.wHour << ":" << var2.wMinute << endl;

    cout << "\n\n Индивидуальное задание\n";
    RECT kurs;
    GetClipCursor(&kurs);
    cout << "1.Координаты курсора = " << kurs.left << "." << kurs.bottom << "." << kurs.right << "." << kurs.top << endl;
    cout << "2.Количество клавиш у мышки: " << GetSystemMetrics(43) << endl;
    cout << "3.Ширина бегунка на горизонтальной полосе прокрутки в пикселях: " << GetSystemMetrics(SM_CXHTHUMB) << endl;
    cout << "4.Курсор заблокирован в пределах {400,400,600,600}\n";
    kurs = { 400,400,600,600 };
    ClipCursor(&kurs);
    return 0;
}