/*
타이머
*/
#include "stdafx.h"
#include "KPro_WINAPI10-1.h"
#include<windowsx.h>

SYSTEMTIME g_time;
RECT r;
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_PAINT)
	{
		PAINTSTRUCT ps;
		HDC h_dc = BeginPaint(hWnd, &ps);
		HFONT h_font = CreateFont(100, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS
			, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"굴림체");
		HFONT h_old_font = (HFONT)SelectObject(h_dc, h_font);
		
		FillRect(h_dc, &r, GetStockBrush(BLACK_BRUSH));
		SetTextColor(h_dc, RGB(255, 255, 0));
		SetBkColor(h_dc, TRANSPARENT);

		int len;
		wchar_t str[30];
		
		GetClientRect(hWnd, &r);
		
		len = wsprintf(str, L"%02d : %02d : %02d", g_time.wHour, g_time.wMinute, g_time.wSecond);
		//TextOut(h_dc, 10, 10, str, len);

		DrawText(h_dc, str, len, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		



		//DrawText(h_dc, str, len, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		
		EndPaint(hWnd, &ps);
	}
	else if (uMsg == WM_CREATE)
	{
		SetTimer(hWnd, 1, 1000, NULL);
	}
	else if (uMsg == WM_TIMER)
	{
		GetLocalTime(&g_time);
		InvalidateRect(hWnd, NULL, TRUE);
	}

	else if (uMsg == WM_DESTROY)
	{
		KillTimer(hWnd, 1);
		PostQuitMessage(0);
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASS wc;

	wchar_t my_class_name[] = L"KPro_WINAPI";
	wc.cbClsExtra = NULL;
	wc.cbWndExtra = NULL;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = my_class_name;
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wc);

	HWND hWnd = CreateWindow(my_class_name, L"KPro_WINAPI",
		WS_OVERLAPPEDWINDOW, 100, 90, 780, 300, NULL, NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);

	}

	return msg.wParam;
}



