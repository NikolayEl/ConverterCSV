#include <Windows.h>
#include "ConvertDefinition.h"

int WINAPI WinMain(HINSTANCE hinst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow)
{
	WNDCLASS SoftwareMainClass = NewWindowClass((HBRUSH)COLOR_WINDOW, LoadCursor(NULL, IDC_HAND), hinst, LoadIcon(NULL, IDI_QUESTION), L"MainWndClass", SoftwareMainProcedure);
	
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
		case OnMenuClicked:
			MessageBoxA(hWnd, "Menu was clicked!", "Menu worked", MB_OK);
			break;
		}

	case WM_CREATE:
		MainWndAddMenus(hWnd);
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

	AppendMenu(RootMenu, MF_STRING, OnMenuClicked, L"Operation");

	SetMenu(hwnd, RootMenu);
}