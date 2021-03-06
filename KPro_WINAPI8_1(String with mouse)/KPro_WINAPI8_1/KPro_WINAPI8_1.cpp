/*
클릭 시 별,
*/
#include "stdafx.h"
#include "KPro_WINAPI8_1.h"
#include<windowsx.h>


int g_click_count = 0;

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_PAINT)
	{
		PAINTSTRUCT ps;
		HDC h_dc = BeginPaint(hWnd, &ps);
		wchar_t str[20];
		wchar_t str2[10][10] = { 0, };
		

		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++) {
				str2[i][j] = '*';
			}
			
		}

		SetBkMode(h_dc, TRANSPARENT);
		for (int i = 1; i <= g_click_count; i++)
		{
			TextOut(h_dc, 10, 10 + i * 10, str2[i-1], i);
		}
		
		int len = wsprintf(str, L"마우스 클릭 횟수 : %d", g_click_count);
		TextOut(h_dc, 100, 100, str, len);

		EndPaint(hWnd, &ps);
	}
	else if (uMsg == WM_LBUTTONDOWN )
	{
		
		g_click_count++;
		if (g_click_count >= 11)
		{
			g_click_count = 0;
		}
		InvalidateRect(hWnd, NULL, TRUE);
		
	}
	else if (uMsg == WM_DESTROY)
	{

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
		WS_OVERLAPPEDWINDOW, 100, 100, 300, 300, NULL, NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);

	}

	return msg.wParam;
}



