/*
타이머
*/
#include "stdafx.h"
#include "KPro_WINAPI9-1.h"
#include<windowsx.h>
//void CALLBACK MyTimerProc(HWND hWnd, UINT nMsg, UINT_PTR nIDEvent, DWORD dwTime);

int g_pos = 10;
RECT g_rect = { 10,10,110,110 };

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_PAINT)
	{
		PAINTSTRUCT ps;
		HDC h_dc = BeginPaint(hWnd, &ps);

		Rectangle(h_dc, g_rect.left+g_pos, g_rect.top, 
			g_rect.right+g_pos, g_rect.bottom);
		EndPaint(hWnd, &ps);
	}
	else if (uMsg == WM_CREATE)
	{
		SetTimer(hWnd, 1, 300, NULL);
		
		return 0;
	}
	else if (uMsg == WM_TIMER)
	{
		g_pos += 20;
		if (g_pos > 660)
		{
			g_pos = 10;
		}
		InvalidateRect(hWnd, NULL, TRUE);
	}
	if (uMsg == WM_DESTROY)
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

void CALLBACK MyTimerProc(HWND hWnd, UINT nMsg, UINT_PTR nIDEvent, DWORD dwTime)
{

}

