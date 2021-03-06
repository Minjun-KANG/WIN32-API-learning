/*
타이머
*/
#include "stdafx.h"
#include "KPro_WINAPI9.h"
#include<windowsx.h>
void CALLBACK MyTimerProc(HWND hWnd, UINT nMsg, UINT_PTR nIDEvent, DWORD dwTime);

int g_x_move = 0;
int g_x_move2 = 0;
int g_step = 1;
int g_step2 = 1;
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_PAINT)
	{
		PAINTSTRUCT ps;
		HDC h_dc = BeginPaint(hWnd, &ps);

		Ellipse(h_dc, g_x_move, 10, 100+g_x_move, 110);
		Rectangle(h_dc, g_x_move2, 130, 100 + g_x_move2, 240);
		EndPaint(hWnd, &ps);
		return 0;
	}
	else if (uMsg == WM_CREATE)
	{
		SetTimer(hWnd, 1, 1000, MyTimerProc);
		SetTimer(hWnd, 2, 2000, NULL); //? NULL? WM_TIMER 호출
		//SetTimer(hWnd, 2, 1500, NULL); //? NULL? WM_TIMER 호출
		return 0;
	}
	else if (uMsg == WM_TIMER)
	{
		//if (wParam == 2) {
			if (g_x_move2 >= 650)
			{
				g_step2 = 0;
			}
			else if (g_x_move2 <= 0)
			{
				g_step2 = 1;
			}
			if (g_step2)
			{
				g_x_move2 += 20;
			}
			else {
				g_x_move2 -= 20;
			}
			InvalidateRect(hWnd, NULL, TRUE); //WM_PAINT 호출
		//}
	}
	if (uMsg == WM_DESTROY) 
	{ 
		KillTimer(hWnd, 1);
		KillTimer(hWnd, 2);
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
	
	/*
	if (g_x_move % 650) 이렇게도 소스코딩할 수 있다.
	{
		g_step = 0;
	}*/
	if (g_x_move >= 650) 
	{
		g_step = 0;
	}
	else if(g_x_move <= 0)
	{
		g_step = 1;
	}
	if (g_step)
	{
		g_x_move += 20;
	}
	else {
		g_x_move -= 20;
	}


	
	InvalidateRect(hWnd, NULL, TRUE); //WM_PAINT 호출
	
}

