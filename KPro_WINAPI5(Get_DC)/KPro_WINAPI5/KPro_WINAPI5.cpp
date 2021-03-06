#include "stdafx.h"
#include "KPro_WINAPI5.h"
#include<windowsx.h>


LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_LBUTTONDOWN)
	{
		HDC h_screen_dc = GetDC(NULL); //모니터 전체 화면의 DC를 얻는다
		//HDC h_screen_dc = GetWindowDC(NULL); 같은 수행줄
		HDC h_dc = GetDC(hWnd);

		BitBlt(h_dc, 0, 0, 300, 200, h_screen_dc, 0, 0, SRCCOPY);
		//BitBlt(h_dc, 10, 10, 300, 200, h_screen_dc, 0, 00, SRCCOPY);
		//BitBlt(h_dc, 10, 10, 300, 200, h_screen_dc, 0, 20, SRCCOPY);
		//BitBlt(h_dc, 10, 10, 300, 200, h_screen_dc, 0, 20, SRCINVERT); //색 반전

		ReleaseDC(hWnd, h_dc);
		ReleaseDC(NULL, h_screen_dc);
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

