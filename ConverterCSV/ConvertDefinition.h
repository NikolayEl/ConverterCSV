#pragma once

#define OnMenuClicked1     1
#define OnMenuClicked2     2
#define OnMenuClicked3     3
#define OnExitSoftware     4
#define OnButton1Clicked   5
#define OnButton2Clicked   6
#define OnButton3Clicked   7
#define OnClearField       8
#define OnHelpSofrware     9

HWND hEditControl;

LRESULT CALLBACK SoftwareMainProcedure(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
WNDCLASS NewWindowClass(HBRUSH BGColor, HCURSOR Cursor, HINSTANCE hInst, HICON Icon, LPCWSTR Name, WNDPROC Procedure);

void MainWndAddMenus(HWND hwnd);
void MainWndAddWidgets(HWND hwnd);