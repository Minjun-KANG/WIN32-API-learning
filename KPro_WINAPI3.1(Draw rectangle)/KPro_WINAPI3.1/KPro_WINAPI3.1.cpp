#include "stdafx.h"
#include "KPro_WINAPI3.1.h"
#include<windowsx.h>


int g_is_click = 0;
RECT g_rect = { 10,10,50,50 }; //Step2
POINT g_prev_pos[1000] = { 0, };
int g_count = 0;

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_PAINT)
	{
		PAINTSTRUCT ps;
		HDC h_dc = BeginPaint(hWnd, &ps);

		if (g_count)
		{
			for (int i = 0; i < g_count; i++)
			{
				Rectangle(h_dc, g_prev_pos[i].x - 15, g_prev_pos[i].y - 15,
					g_prev_pos[i].x + 15, g_prev_pos[i].y + 15);
			}
		}

		EndPaint(hWnd, &ps);
		return 0;
	}
	if (uMsg == WM_LBUTTONDOWN)
	{
		HDC h_dc = GetDC(hWnd);
		
		
		g_prev_pos[g_count].x = GET_X_LPARAM(lParam);
		g_prev_pos[g_count].y = GET_Y_LPARAM(lParam);
		g_count++;

		Rectangle(h_dc, g_prev_pos[g_count-1].x - 15, g_prev_pos[g_count - 1].y - 15,
			g_prev_pos[g_count - 1].x + 15, g_prev_pos[g_count - 1].y + 15);

		ReleaseDC(hWnd, h_dc);

	}
	if (uMsg == WM_DESTROY) { PostQuitMessage(0); }
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASS wc;

	wchar_t my_class_name[] = L"KPro_WINAPI2";
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

	HWND hWnd = CreateWindow(my_class_name, L"KPro_WINAPI2",
		WS_OVERLAPPEDWINDOW, 100, 90, 400, 350, NULL, NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);

	}

	return msg.wParam;
}

