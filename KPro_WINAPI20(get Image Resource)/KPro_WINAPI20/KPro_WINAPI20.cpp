
#include "stdafx.h"
#include "KPro_WINAPI20.h"
#include<windowsx.h>
HINSTANCE g_instance;
RECT g_rect;
typedef struct Main_C_POSITION
{
	int x;
	int y;
}MP;
MP g_mp = { 400,350 };
void onekeydown(HWND, WPARAM);
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_PAINT)
	{
		
		PAINTSTRUCT ps;
		HDC MemDC, hdc = BeginPaint(hWnd, &ps);
		HBITMAP bit, obit;
		
		MemDC = CreateCompatibleDC(hdc); //hdc와 속성을 동일하게 함, hdc에 비트맵 복사는 안되기 때문

		bit = LoadBitmap(g_instance, MAKEINTRESOURCE(IDB_ONE));
		
		obit = (HBITMAP)SelectObject(MemDC, bit);
		BitBlt(hdc, -20, -20, 343, 606, MemDC, 0, 0, SRCCOPY);
		bit = LoadBitmap(g_instance, MAKEINTRESOURCE(IDB_nemo));
		SelectObject(MemDC, bit);
		BitBlt(hdc, 700, -20, 343, 606, MemDC, 0, 0, SRCCOPY);
		bit = LoadBitmap(g_instance, MAKEINTRESOURCE(IDB_MAINC));
		SelectObject(MemDC, bit);
		BitBlt(hdc, g_mp.x, g_mp.y, 187, 189, MemDC, 0, 0, SRCCOPY);
		//BitBlt(hdc, g_main_c.left, g_main_c.top, g_main_c.right, g_main_c.bottom, MemDC, 0, 0, SRCCOPY);
		SelectObject(MemDC, bit);

		DeleteObject(bit);
		DeleteDC(MemDC);
		EndPaint(hWnd, &ps);
	}
	else if (uMsg == WM_CREATE)
	{
		GetClientRect(hWnd, &g_rect);
	}
	else if (uMsg == WM_KEYDOWN)
	{
		onekeydown(hWnd, wParam);
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
	g_instance = hInstance;
	HBRUSH h_brush = GetStockBrush(WHITE_BRUSH);

	wchar_t my_class_name[] = L"KPro_WINAPI";
	wc.cbClsExtra = NULL;
	wc.cbWndExtra = NULL;
	wc.hbrBackground = h_brush;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = my_class_name;
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wc);

	HWND hWnd = CreateWindow(my_class_name, L"KPro_WINAPI",
		WS_OVERLAPPEDWINDOW, 10, 10, 1024, 600, NULL, NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);

	}

	return msg.wParam;
}

void onekeydown(HWND hWnd, WPARAM wParam)
{
	if (wParam == VK_LEFT || wParam == 0x41)
	{
		g_mp.x -= 5;
	}
	else if (wParam == VK_RIGHT || wParam == 0x44)
	{
		g_mp.x += 5;
	}
	else if (wParam == VK_UP || wParam == 0x57)
	{
		g_mp.y -= 5;
	}
	else if (wParam == VK_DOWN || wParam == 0x53)
	{
		g_mp.y += 5;
	}
	InvalidateRect(hWnd, &g_rect, TRUE);
}	