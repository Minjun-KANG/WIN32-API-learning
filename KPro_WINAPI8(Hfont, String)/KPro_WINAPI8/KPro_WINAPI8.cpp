/*
문자열 출력
*/
#include "stdafx.h"
#include "KPro_WINAPI8.h"
#include<windowsx.h>


LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_PAINT)
	{
		PAINTSTRUCT ps;
		HDC h_dc = BeginPaint(hWnd, &ps);

		wchar_t str[30];
		int len;

		SetBkMode(h_dc, TRANSPARENT); //문자열의 배경색 투명하게
		HFONT h_font = CreateFont(30, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS
			, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"굴림체");
		HGDIOBJ h_old_font = SelectObject(h_dc, h_font);

		//TextOut(h_dc, 10, 10, L"구구단", 3);
		RECT r = { 0,10,770,50 };
		//FillRect(h_dc, &r, (HBRUSH)GetStockBrush(DKGRAY_BRUSH));

		DrawText(h_dc, L"구구단", 3, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		SelectObject(h_dc, h_old_font);

		DeleteObject(h_font);

		SetTextColor(h_dc, RGB(20, 0, 189));

		for (int j = 2; j < 10; j++) {
			for (int i = 1; i < 10; i++)
			{
				len = wsprintf(str, L"%d * %d * %d", j, i, j * i); //wsprintf, 문자열의 길이반환
				TextOut(h_dc, 10+(j-2)*100, 30 + i * 20, str, len);
			}
		}


		EndPaint(hWnd, &ps);
		return 0;
	}
	if (uMsg == WM_DESTROY) { PostQuitMessage(0); }
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

