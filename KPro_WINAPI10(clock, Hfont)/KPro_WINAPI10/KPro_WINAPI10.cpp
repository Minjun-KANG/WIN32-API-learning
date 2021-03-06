/*
타이머
*/
#include "stdafx.h"
#include "KPro_WINAPI10.h"
#include<windowsx.h>

SYSTEMTIME time;

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_PAINT)
	{
		PAINTSTRUCT ps;
		HDC h_dc = BeginPaint(hWnd, &ps);
		HFONT h_font = CreateFont(100, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS
			, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"굴림체");
		HFONT h_old_font = (HFONT)SelectObject(h_dc, h_font);

		SetTextColor(h_dc, RGB(255, 255, 0));

		SetBkMode(h_dc, TRANSPARENT);

		wchar_t str[30];
		int len;
		//RECT r = { 0, 10, 780, 250 };
		RECT r;
		GetClientRect(hWnd, &r);

		FillRect(h_dc, &r, GetStockBrush(BLACK_BRUSH));
		len = wsprintf(str, L"%02d : %02d : %02d", time.wHour, time.wMinute, time.wSecond);
		DrawText(h_dc, str, len, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);


		DeleteObject(h_font);
		EndPaint(hWnd, &ps);
		return 0;
	}
	else if (uMsg == WM_CREATE)
	{
		SetTimer(hWnd, 1, 1000, NULL);
		return 0;
	}
	else if (uMsg == WM_TIMER)
	{
		if (wParam == 1)
		{
			
			GetLocalTime(&time); //컴퓨터의 지역시간

			InvalidateRect(hWnd, NULL, TRUE);
			//GetSystemTime() //UTC 기반 //서울 +9
		}
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



