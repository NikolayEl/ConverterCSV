#include <Windows.h>
#include "ConvertDefinition.h"
#include <string>

using namespace std;

int WINAPI WinMain(HINSTANCE hinst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow)
{
	WNDCLASS SoftwareMainClass = NewWindowClass((HBRUSH)COLOR_WINDOW, LoadCursor(NULL, IDC_ARROW), hinst, LoadIcon(NULL, IDI_QUESTION), L"MainWndClass", SoftwareMainProcedure);
	
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
			MessageBoxA(hWnd, "File is open!", "MENU:", MB_OK);
			break;
		case OnButtonClicked:
			MessageBoxA(hWnd, "Thanks!", "Button clicked", MB_OK);
			break;
		case OnMenuClicked2:
			MessageBoxA(hWnd, "Menu 2 was clicked!", "Menu worked", MB_OK);
			break;
		case OnMenuClicked3:
			MessageBoxA(hWnd, "Menu 3 was clicked!", "Menu worked", MB_OK);
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

	AppendMenu(SubMenu, MF_STRING, OnMenuClicked1, L"File open");
	AppendMenu(SubMenu, MF_STRING, OnMenuClicked2, L"Menu 2");
	AppendMenu(SubMenu, MF_STRING, OnMenuClicked3, L"Menu 3");
	AppendMenu(SubMenu, MF_SEPARATOR, NULL, NULL);
	AppendMenu(SubMenu, MF_STRING, OnExitSoftware, L"Exit");


	AppendMenu(RootMenu, MF_POPUP, (UINT_PTR)SubMenu, L"Operation");

	SetMenu(hwnd, RootMenu);
}

void MainWndAddWidgets(HWND hWnd)
{
	CreateWindowA("static", "Operation Status:", WS_VISIBLE | WS_CHILD, 5, 5, 990, 20,hWnd, NULL, NULL, NULL); //Название виджета
	CreateWindowA("static", "...ready", WS_VISIBLE | WS_CHILD, 5, 5, 990, 20, hWnd, NULL, NULL, NULL); //
	CreateWindowA("edit", "This is edit control", WS_VISIBLE | WS_CHILD, 5, 30, 990, 20, hWnd, NULL, NULL, NULL);
	CreateWindowA("button", "Open file", WS_VISIBLE | WS_CHILD, 450, 350, 120, 30, hWnd, (HMENU)OnButtonClicked, NULL, NULL);
}