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
			SetWindowTextA(hEditControl, "File is open!");
			break;
		case OnMenuClicked2:
			SetWindowTextA(hEditControl, "income calculated!");
			break;
		case OnMenuClicked3:
			SetWindowTextA(hEditControl, "result saved");
			break;
		case OnButton1Clicked:
			SetWindowTextA(hEditControl, "File is open!");
			break;
		case OnButton2Clicked:
			SetWindowTextA(hEditControl, "income calculated!");
			break;
		case OnButton3Clicked:
			SetWindowTextA(hEditControl, "result saved");
			break;
		case OnClearField:
			SetWindowTextA(hEditControl, "");
			break;
		case OnHelpSofrware:
			SetWindowTextA(hEditControl, "This program is written for personal use and is not intended for distribution. Elshin N.V.");
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
	CreateWindowA("static", "Operation Status:", WS_VISIBLE | WS_CHILD, 5, 5, 990, 20,hWnd, NULL, NULL, NULL); //Название виджета
	//CreateWindowA("static", "wating for the command", WS_VISIBLE | WS_CHILD, 5, 5, 990, 20, hWnd, NULL, NULL, NULL); //
	hEditControl = CreateWindowA("edit", "wating for the command", WS_VISIBLE | WS_CHILD | ES_MULTILINE, 5, 5, 990, 330, hWnd, NULL, NULL, NULL);
	CreateWindowA("button", "Open file", WS_VISIBLE | WS_CHILD, 50, 350, 120, 30, hWnd, (HMENU)OnButton1Clicked, NULL, NULL);
	CreateWindowA("button", "Calculate income", WS_VISIBLE | WS_CHILD, 200, 350, 120, 30, hWnd, (HMENU)OnButton2Clicked, NULL, NULL);
	CreateWindowA("button", "Save result", WS_VISIBLE | WS_CHILD, 350, 350, 120, 30, hWnd, (HMENU)OnButton3Clicked, NULL, NULL);
	CreateWindowA("button", "Clear", WS_VISIBLE | WS_CHILD, 490, 350, 120, 30, hWnd, (HMENU)OnClearField, NULL, NULL);
	CreateWindowA("button", "Exit", WS_VISIBLE | WS_CHILD, 800, 350, 120, 30, hWnd, (HMENU)OnExitSoftware, NULL, NULL);
}