#include "stdafx.h"
#include "KPro_WINAPI2.h"
#include<windowsx.h>

int g_is_click = 0;
int g_x, g_y;
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	/*
	if (uMsg == WM_LBUTTONDOWN)
	{
		HDC h_dc = GetDC(hWnd);
		int x = lParam & 0x0000ffff;
		int y = (lParam>>16) & 0x0000FFFF;
		Rectangle(h_dc, x, y, x+100, y+100);
		
		//Ellipse(h_dc, 30, 30, 90, 90);



		HDC h_dc = GetDC(hWnd);
		
		Rectangle(h_dc, 100, 100, 200, 200);
		ReleaseDC(hWnd, h_dc);
	}
*/
	/*
	if (uMsg == WM_LBUTTONDOWN) //클릭시 도형그리기
	{
		HDC h_dc = GetDC(hWnd);
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);

		if (MK_CONTROL & wParam)
		{
			Ellipse(h_dc, x - 15, y - 15, x + 15, y + 15);
		}
		
		else
		{
			Rectangle(h_dc, x - 15, y - 15, x + 15, y + 15);
		}


	}*/
	
	/*
	if (uMsg == WM_MOUSEMOVE) {

		HDC h_dc = GetDC(hWnd);
		int x = lParam & 0x0000FFFF;
		int y = (lParam >> 16) & 0x0000FFFF;
		if (MK_CONTROL & wParam)
		{
			Ellipse(h_dc, x - 15, y - 15, x + 15, y + 15);
		}
		else
		{
			Rectangle(h_dc, x - 30, y - 30, x + 30, y + 30);
		}
		ReleaseDC(hWnd, h_dc);

	}
	*/
	/*
	if (uMsg == WM_MOUSEMOVE) {
		if (wParam & MK_LBUTTON)
		{
			HDC h_dc = GetDC(hWnd);
			int x = lParam & 0x0000FFFF;
			int y = (lParam >> 16) & 0x0000FFFF;
			if (MK_CONTROL & wParam)
			{
				Ellipse(h_dc, x - 15, y - 15, x + 15, y + 15);
			}
			else
			{
				Rectangle(h_dc, x - 30, y - 30, x + 30, y + 30);
			}
			ReleaseDC(hWnd, h_dc);
		}
	}
	
	*/
	/*
	if (uMsg == WM_LBUTTONDOWN)
	{
		g_is_click = 1;
	}
	else if (uMsg == WM_LBUTTONUP)
	{
		g_is_click = 0;
	}
	else if (uMsg == WM_MOUSEMOVE) {
		if (g_is_click)
		{
			HDC h_dc = GetDC(hWnd);

			//MoveToEx(h_dc, 10, 10, NULL);
			//LineTo(h_dc, 100, 100);

			int x = GET_X_LPARAM(lParam); //#include<windowsx.h> 을 참조해야만 사용가능
			int y = GET_Y_LPARAM(lParam);


			Ellipse(h_dc, x - 15, y - 15, x + 15, y + 15);

			ReleaseDC(hWnd, h_dc);
		}
	}
	*/
	/*
	if (uMsg == WM_LBUTTONDOWN)
	{
		g_is_click = 1;
		HDC h_dc = GetDC(hWnd);

		int x = GET_X_LPARAM(lParam);
		int y = GET_Y_LPARAM(lParam);

		MoveToEx(h_dc, x, y, NULL);

		ReleaseDC(hWnd, h_dc);
	}
	else if (uMsg == WM_LBUTTONUP)
	{
		g_is_click = 0;
	}
	else if (uMsg == WM_MOUSEMOVE) {
		if (g_is_click)
		{
			HDC h_dc = GetDC(hWnd);

			int x = GET_X_LPARAM(lParam);
			int y = GET_Y_LPARAM(lParam);
			LineTo(h_dc, x, y);

			ReleaseDC(hWnd, h_dc);
		}
	}
	
	*/
	/*
	if (uMsg == WM_LBUTTONDOWN)
	{
		g_is_click = 1;
		g_x = GET_X_LPARAM(lParam);
		g_y = GET_Y_LPARAM(lParam);
	}
	else if (uMsg == WM_LBUTTONUP)
	{
		g_is_click = 0;
	}
	else if (uMsg == WM_MOUSEMOVE) {
		if (g_is_click)
		{
			HDC h_dc = GetDC(hWnd);
			MoveToEx(h_dc, g_x, g_y, NULL);
			int x = GET_X_LPARAM(lParam);
			int y = GET_Y_LPARAM(lParam);
			LineTo(h_dc, x, y);

			ReleaseDC(hWnd, h_dc);
		}
	}
	*/

	if (uMsg == WM_LBUTTONDOWN)
	{
		g_is_click = 1;
		g_x = GET_X_LPARAM(lParam);
		g_y = GET_Y_LPARAM(lParam);
	}
	else if (uMsg == WM_LBUTTONUP)
	{
		g_is_click = 0;
	}
	else if (uMsg == WM_MOUSEMOVE) {
		if (g_is_click)
		{
			HDC h_dc = GetDC(hWnd);
			MoveToEx(h_dc, g_x, g_y, NULL);
			int x = GET_X_LPARAM(lParam);
			int y = GET_Y_LPARAM(lParam);
			LineTo(h_dc, x, y);
			g_x = x;
			g_y = y;

			ReleaseDC(hWnd, h_dc);
		}
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

