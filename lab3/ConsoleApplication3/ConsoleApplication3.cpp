#include <iostream>
#include <conio.h>
#include <windows.h>
#include <tlhelp32.h>
#include <locale>
#include <stdio.h>
#include <string.h>

#define cout wcout
#define cin wcin
#define STRING_LENGTH 256
#pragma warning(disable : 4996)

using namespace std;

void Vivod(HMODULE hModule, wchar_t* longName);
int GetFileName(wchar_t* outName, wchar_t* fullName, const int bufferLength);

void main(int argv, char **argc){
	setlocale(LC_ALL, "rus");
	cout.imbue(locale("rus_rus.1251"));
	char* param = new char[STRING_LENGTH];
	wchar_t* longName = new wchar_t[STRING_LENGTH];
	strcpy(param ,argc[0]);
	wchar_t* shortName = new wchar_t[STRING_LENGTH];

	bool exit = true;
	while (exit)
	{
		cout << "\nВыберите действие:" << endl
			<< "1: Задать Name" << endl
			<< "2: Задать FName" << endl
			<< "3: Задать Handle" << endl
			<< "Выбор: ";
		int n = 0;
		cin >> n;
		HMODULE hModule;
		switch (n)
		{
		case 1:
		{
			int a = 0;
			cout << endl << "Введите Name: ";
			cin >> shortName;
			GetModuleFileName(GetModuleHandle(shortName), longName, STRING_LENGTH);
			hModule = GetModuleHandle(longName);
			Vivod(hModule, longName);
			break;
		}
		case 2:
		{
			cout << endl << "Введите FName: ";
			cin >> longName;
			GetFileName(shortName, longName, STRING_LENGTH);
			hModule = GetModuleHandle(longName);
			Vivod(hModule, longName);
			break;
		}
		case 3:
		{
			cout << endl << "Введите Handle: ";
			wchar_t* temp = new wchar_t[10];
			cin >> temp;
			wchar_t* endptr;
			long num = wcstoul(temp, &endptr, 16);
			hModule = (HMODULE)num;
			GetModuleFileName(hModule, longName, STRING_LENGTH);
			Vivod(hModule, longName);
			delete[] temp;
			break;
		}
		}
	}
	delete[] param;
	delete[] longName;
	delete[] shortName;
}

int GetFileName(wchar_t* outName, wchar_t* fullName, const int bufferLength)
{
	wchar_t* name = wcsrchr(fullName, L'\\');
	if (name == NULL)
	{
		wcsncpy(outName, fullName, bufferLength);
		return 0;
	}
	else
	{
		wcsncpy(outName, name + 1, bufferLength);
		return 1;
	}
}

void Vivod(HMODULE hModule, wchar_t* longName)
{
	wchar_t* shortName = new wchar_t[STRING_LENGTH];
	GetFileName(shortName, longName, STRING_LENGTH);
	cout << "\nHandle: " << hModule << endl << "Name: " << shortName << endl << "FName: " << longName << endl;
	delete shortName;
}

