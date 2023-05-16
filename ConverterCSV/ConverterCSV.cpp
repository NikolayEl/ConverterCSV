#include <Windows.h>
#include "ConvertDefinition.h"
#include <string>
#include "Resource1.h"
#include <iostream>

using namespace std;


int WINAPI WinMain(HINSTANCE hinst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow)
{
	setlocale(LC_ALL, "");

	WNDCLASS SoftwareMainClass = NewWindowClass((HBRUSH)COLOR_WINDOW, LoadCursor(NULL, IDC_ARROW), hinst, LoadIcon(hinst, MAKEINTRESOURCE(IDI_ICON2)), L"MainWndClass", SoftwareMainProcedure);
	
	if (!RegisterClassW(&SoftwareMainClass)) { return -1; };
	MSG SoftwareMainMessage = { 0 };

	CreateWindow(L"MainWndClass", L"Conver SVC", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 1000, 500, NULL, NULL, NULL, NULL);

	while (GetMessage(&SoftwareMainMessage, NULL, NULL, NULL))
	{
		TranslateMessage(&SoftwareMainMessage);
		DispatchMessage(&SoftwareMainMessage);
	}
	return 0;

}

WNDCLASS NewWindowClass(HBRUSH BGColor, HCURSOR Cursor, HINSTANCE hInst, HICON Icon, LPCWSTR Name, WNDPROC Procedure)
{
	WNDCLASS NWC = { 0 };

	NWC.hCursor = Cursor;
	NWC.hIcon = Icon;
	NWC.hInstance = hInst;
	NWC.lpszClassName = Name;
	NWC.hbrBackground = BGColor;
	NWC.lpfnWndProc = Procedure;

	return NWC;
}

LRESULT CALLBACK SoftwareMainProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
	case WM_COMMAND:
		switch (wp)
		{
		case OnMenuClicked1:
			LoadData("C:\\Users\\Elshin\\Documents\\My Project\\proba.csv");
			break;
		case OnMenuClicked2:
			SetWindowTextA(hStaticControl, "income calculated!");
			break;
		case OnMenuClicked3:
			SaveData("C:\\Users\\Elshin\\Documents\\My Project\\size.txt");
			break;
		case OnButton1Clicked:
			LoadData("C:\\Users\\Elshin\\Documents\\My Project\\size.txt");
			break;
		case OnButton2Clicked:
			SetWindowTextA(hStaticControl, "income calculated!");
			break;
		case OnButton3Clicked:
			SaveData("C:\\Users\\Elshin\\Documents\\My Project\\size.txt");
			break;
		case OnClearField:
			SetWindowTextA(hStaticControl, "");
			break;
		case OnHelpSofrware:
			SetWindowTextA(hStaticControl, "This program is written for personal use and is not intended for distribution. Elshin N.V.");
			break;
		case OnSaveFile:
			SaveData("C:\\Users\\Elshin\\Documents\\My Project\\size.txt");
			break;
		case OnLoadFile:
			LoadData("C:\\Users\\Elshin\\Documents\\My Project\\size.txt");
			break;
		case OnExitSoftware:
			PostQuitMessage(0);
			break;
		}
		break;

	case WM_CREATE:
		MainWndAddMenus(hWnd);
		MainWndAddWidgets(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default: return DefWindowProc(hWnd, msg, wp, lp);
	}
}

void MainWndAddMenus(HWND hwnd)
{
	HMENU RootMenu = CreateMenu();
	HMENU SubMenu = CreateMenu();
	HMENU HelpMenu = CreateMenu();

	AppendMenu(SubMenu, MF_STRING, OnMenuClicked1, L"File open");
	AppendMenu(SubMenu, MF_STRING, OnMenuClicked2, L"Calculate income");
	AppendMenu(SubMenu, MF_STRING, OnMenuClicked3, L"Save result");
	AppendMenu(SubMenu, MF_SEPARATOR, NULL, NULL);
	AppendMenu(SubMenu, MF_STRING, OnExitSoftware, L"Exit");
	AppendMenu(HelpMenu, MF_STRING, OnHelpSofrware, L"About");


	AppendMenu(RootMenu, MF_POPUP, (UINT_PTR)SubMenu, L"File");
	AppendMenu(RootMenu, MF_POPUP, (UINT_PTR)HelpMenu, L"Help");

	SetMenu(hwnd, RootMenu);
}

void MainWndAddWidgets(HWND hWnd)
{
	//CreateWindowA("static", "Operation Status:", WS_VISIBLE | WS_CHILD, 5, 5, 990, 20,hWnd, NULL, NULL, NULL); //Название виджета
	//CreateWindowA("static", "wating for the command", WS_VISIBLE | WS_CHILD, 5, 5, 990, 20, hWnd, NULL, NULL, NULL); //
	hStaticControl = CreateWindowA("static", "wating for the command", WS_VISIBLE | WS_CHILD | WS_VSCROLL, 5, 5, 945, 330, hWnd, NULL, NULL, NULL);
	CreateWindowA("button", "Open file", WS_VISIBLE | WS_CHILD, 50, 350, 120, 30, hWnd, (HMENU)OnButton1Clicked, NULL, NULL);
	CreateWindowA("button", "Calculate income", WS_VISIBLE | WS_CHILD, 200, 350, 120, 30, hWnd, (HMENU)OnButton2Clicked, NULL, NULL);
	CreateWindowA("button", "Save result", WS_VISIBLE | WS_CHILD, 350, 350, 120, 30, hWnd, (HMENU)OnButton3Clicked, NULL, NULL);
	CreateWindowA("button", "Clear", WS_VISIBLE | WS_CHILD, 490, 350, 120, 30, hWnd, (HMENU)OnClearField, NULL, NULL);
	CreateWindowA("button", "Exit", WS_VISIBLE | WS_CHILD, 815, 350, 120, 30, hWnd, (HMENU)OnExitSoftware, NULL, NULL);
}

void SaveData(LPCSTR path)
{
	setlocale(LC_ALL, "");
	HANDLE FileToSave = CreateFileA(
		path,
		GENERIC_WRITE,
		0,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	
	int saveLenth = GetWindowTextLength(hStaticControl) + 1;
	char* data = new char[saveLenth];

	saveLenth = GetWindowTextA(hStaticControl, data, saveLenth);

	DWORD bytesIterated;
	ReadFile(FileToSave, data, saveLenth, &bytesIterated, NULL);

	SetWindowTextA(hStaticControl, buffer);

	CloseHandle(FileToSave);
}
void LoadData(LPCSTR path)
{
	setlocale(LC_ALL, "");
	HANDLE FileToLoad = CreateFileA(
		path,
		GENERIC_READ,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
		
	DWORD bytesIterated;
	ReadFile(FileToLoad, buffer, TextBufferSize, &bytesIterated, NULL);

	SetWindowTextA(hStaticControl, buffer);

	CloseHandle(FileToLoad);
}
