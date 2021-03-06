#include "stdafx.h"
#include "KPro_WINAPI17.h"
#include<windowsx.h>

void Onkeydown(HWND, WPARAM);

RECT g_r = { 10,10,40,40 };
RECT g_client_r;

typedef struct _rgb
{
	int red;
	int green;
	int blue;
}RGB;

RGB g_rgb;
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_CREATE)
	{
		GetClientRect(hWnd, &g_client_r);
		
		
		g_r.left = g_client_r.right / 2 - 20;
		g_r.right = g_client_r.right / 2 + 20;
		g_r.top = g_client_r.bottom / 2 - 20;
		g_r.bottom = g_client_r.bottom / 2 + 20;
		
	}
	if (uMsg == WM_PAINT)
	{
		
		PAINTSTRUCT ps;
		
		HDC h_dc = BeginPaint(hWnd, &ps);
		HBRUSH h_brush = CreateSolidBrush(RGB(g_rgb.red, g_rgb.green, g_rgb.blue));
		HBRUSH h_old_brush = (HBRUSH)SelectObject(h_dc, h_brush);
		
		SelectObject(h_dc, GetStockPen(BLACK_PEN));

		Rectangle(h_dc, g_r.left, g_r.top, g_r.right, g_r.bottom);

		
		SelectObject(h_dc, h_old_brush);
		DeleteObject(h_brush);
		DeleteObject(h_old_brush);
		EndPaint(hWnd, &ps);
	}
	else if (uMsg == WM_KEYDOWN)
	{
		Onkeydown(hWnd, wParam);
		
	}
	else if (uMsg == WM_DESTROY)
	{
		PostQuitMessage(0);
	}
	return(DefWindowProc(hWnd, uMsg, wParam, lParam));
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
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
		50, 50, 640, 374, NULL, NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

void Onkeydown(HWND hWnd, WPARAM wParam)
{
	if (wParam) {
		if (wParam == VK_LEFT || wParam == 0x41)
		{
			if (g_client_r.left + 10 <= g_r.left) {
				g_r.left -= 10;
				g_r.right -= 10;
			}
		}
		else if (wParam == VK_RIGHT || wParam == 0x44)
		{
			if (g_client_r.right - 10 >= g_r.right) {
				g_r.left += 10;
				g_r.right += 10;
			}
		}
		else if (wParam == VK_UP || wParam == 0x57)
		{
			if (g_client_r.top + 10 <= g_r.top) {
				g_r.top -= 10;
				g_r.bottom -= 10;
			}
		}
		else if (wParam == VK_DOWN || wParam == 0x53)
		{
			if (g_client_r.bottom - 10 >= g_r.bottom) {
				g_r.bottom += 10;
				g_r.top += 10;

			}
		}
		else if (wParam == VK_F1)
		{
			if (g_rgb.red <= 250) {
				g_rgb.red += 10;
			}
			else {
				g_rgb.red = 0;
			}
		}
		else if (wParam == VK_F2)
		{
			if (g_rgb.green <= 250) {
				g_rgb.green += 10;
			}
			else {
				g_rgb.green = 0;
			}
		}
		else if (wParam == VK_F3)
		{
			if (g_rgb.blue <= 250) {
				g_rgb.blue += 10;
			}
			else {
				g_rgb.blue = 0;
			}
		}
		else if (wParam == VK_F5)
		{
			if (g_r.right - g_r.left <= 100) 
			{
				g_r.left--;
				g_r.top--;
				g_r.bottom++;
				g_r.right++;
			}
		}
		else if (wParam == VK_F6)
		{
			if (g_r.right - g_r.left >= 10)
			{
				g_r.left++;
				g_r.top++;
				g_r.bottom--;
				g_r.right--;
			}
		}
		InvalidateRect(hWnd,&g_client_r, TRUE);
	}
}
