#include <iostream>
#include <conio.h>
#include <windows.h>
#include <tlhelp32.h>
#include <locale>
#include <stdio.h>
#include <string.h>
#define cout wcout

using namespace std;

void ShowProcessEntry(PROCESSENTRY32& entry)
{
	cout << "\n\nth32ProcessID = " << entry.th32ProcessID;
	cout << "\nth32ParentProcessID = " << entry.th32ParentProcessID;
	cout << "\ncntThreads = " << entry.cntThreads;
	cout << "\npcPriClassBase = " << entry.pcPriClassBase;
	cout << "\nszExeFile = " << entry.szExeFile;
	cout << "\ndwSize = " << entry.dwSize;
}

void ShowThreadEntry(THREADENTRY32& entry)
{
	cout << "\n\nth32ThreadID = " << entry.th32ThreadID;
	cout << "\nth32OwnerProcessID = " << entry.th32OwnerProcessID;
	cout << "\ntpBasePri = " << entry.tpBasePri;
	cout << "\ndwSize = " << entry.dwSize;
}

void ShowModuleEntry(MODULEENTRY32& entry)
{
	cout << "\n\nth32ModuleID \t= \t" << entry.th32ModuleID;
	cout << "\nth32ProcessID \t= \t" << entry.th32ProcessID;
	cout << "\nGlblcntUsage \t= \t" << entry.GlblcntUsage;
	cout << "\nProccntUsage \t= \t" << entry.ProccntUsage;
	cout << "\nmodBaseAddr \t= \t" << entry.modBaseAddr;
	cout << "\nmodBaseSize \t= \t" << entry.modBaseSize;
	cout << "\nhModule \t= \t" << entry.hModule;
	cout << "\nszModule \t= \t" << entry.szModule;
	cout << "\nszExePath \t= \t" << entry.szExePath;
	cout << "\ndwSize = " << entry.dwSize;
}

void ShowProcesses()
{
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	cout << "\nSnapshot ID = " << hSnapshot;
	PROCESSENTRY32 entry;
	entry.dwSize = sizeof(PROCESSENTRY32);
	BOOL fRepeat = Process32First(hSnapshot, &entry);
	ShowProcessEntry(entry);
	fRepeat = Process32Next(hSnapshot, &entry);
	CloseHandle(hSnapshot);
	cout << "\n\n=== Конец данных о процессах ===\n\n";
}

void ShowThreads()
{
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
	cout << "\nSnapshot ID = " << hSnapshot;
	THREADENTRY32 entry;
	entry.dwSize = sizeof(THREADENTRY32);
	BOOL fRepeat = Thread32First(hSnapshot, &entry);
	DWORD dwCurentProcessId = GetCurrentProcessId();
	while (fRepeat)
	{
		if (entry.th32OwnerProcessID == dwCurentProcessId)
		{
			ShowThreadEntry(entry);
		}
		fRepeat = Thread32Next(hSnapshot, &entry);
	}
	CloseHandle(hSnapshot);
	cout << "\n\n=== Конец данных о потоках ===\n\n";
}

void ShowModules()
{
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, 0);
	cout << "\nSnapshot ID = " << hSnapshot;
	MODULEENTRY32 entry;
	entry.dwSize = sizeof(MODULEENTRY32);
	BOOL fRepeat = Module32First(hSnapshot, &entry);
	ShowModuleEntry(entry);
	fRepeat = Module32Next(hSnapshot, &entry);
	CloseHandle(hSnapshot);
	cout << "\n\n=== Конец данных о модулях ===\n\n";
}


int main() {

	cout << "Zadanie 2" << endl;

	setlocale(LC_ALL, "rus");
	cout.imbue(locale("rus_rus.1251"));
	DWORD dCurrentId = GetCurrentProcessId();
	HANDLE hCurrentPseudo = GetCurrentProcess();
	HANDLE hCurrentIdDup;
	DuplicateHandle(hCurrentPseudo, hCurrentPseudo, hCurrentPseudo, &hCurrentIdDup, 0, FALSE, DUPLICATE_SAME_ACCESS);
	HANDLE hCurrentIdOpen = OpenProcess(PROCESS_DUP_HANDLE, TRUE, dCurrentId);
	BOOL fClosedDup = CloseHandle(hCurrentIdDup);
	BOOL fClosedOpen = CloseHandle(hCurrentIdOpen);
	cout << "\nИдентификатор текущего процесса: " << dCurrentId
		<< "\nПсевдодескриптор текущего процесса: " << hCurrentPseudo
		<< "\nДескриптор, полученный функцией DuplicateHandle: " << hCurrentIdDup
		<< "\nДескриптор, полученный функцией OpenProcess: " << hCurrentIdOpen
		<< "\nЗакрываем дескриптор, полученный функцией OpenProcess: " << fClosedOpen
		<< "\nЗакрываем дескриптор, полученный функцией DuplicateHandle: " << fClosedDup << endl;

	cout << "\nZadanie 3" << endl;

	cout << "\n\n=== Процессы ===\n";
	ShowProcesses();
	cout << "\n\n=== Потоки ===\n";
	ShowThreads();
	cout << "\n\n=== Модули ===\n";
	ShowModules();
}

