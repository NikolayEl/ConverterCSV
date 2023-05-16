#pragma once

#define OnMenuClicked1     1
#define OnMenuClicked2     2
#define OnMenuClicked3     3
#define OnExitSoftware     4
#define OnButtonClicked    5

LRESULT CALLBACK SoftwareMainProcedure(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
WNDCLASS NewWindowClass(HBRUSH BGColor, HCURSOR Cursor, HINSTANCE hInst, HICON Icon, LPCWSTR Name, WNDPROC Procedure);

void MainWndAddMenus(HWND hwnd);
void MainWndAddWidgets(HWND hwnd);