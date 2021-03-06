#include "stdafx.h"
#include "KPro_WINAPI13-1.h"
#include<windowsx.h>
#include<string.h>




LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	if (uMsg == WM_PAINT)
	{
		PAINTSTRUCT ps;
		HDC h_dc = BeginPaint(hWnd, &ps);

		EndPaint(hWnd, &ps);
	
	}
	else if (uMsg == WM_LBUTTONDOWN)
	{
		HWND h_find_wnd = FindWindow(L"Notepad", NULL);
		if (h_find_wnd)
		{
			HWND h_edit_wnd = FindWindowEx(h_find_wnd, NULL, L"Edit", NULL);
			if (h_edit_wnd)
			{
				wchar_t str[256];
				SendMessage(h_edit_wnd, WM_GETTEXT, 256, (LPARAM)str);

				MessageBox(hWnd, str, L"제목줄", MB_OK);
			}
		}


		/*
		HWND h_find_wnd = FindWindow(L"Notepad", NULL); //내가 원하는 윈도우를 찾는다 WNDCLASS or WNDNAME으로 
														//부모WND만 찾음


		if (h_find_wnd) // 찾았으면
		{
			HDC h_dc = GetDC(hWnd);
			HWND h_edit_wnd = FindWindowEx(h_find_wnd, NULL, L"Edit", NULL); //가장 처음에있는 윈도우부터 찾겠다 - >
			//NULL, WNDCLASS가 Edit인, 제목은 신경쓰지 않는다
			if (h_edit_wnd)
			{
				wchar_t str[256];
				//SendMessage(h_edit_wnd, WM_SETTEXT, NULL, (LPARAM)L"안녕하다"); //다른 프로그램의 윈도우까지 메세지를 보냄
				SendMessage(h_edit_wnd, WM_GETTEXT, 256, (LPARAM)str);
				//SetBkColor(h_dc, TRANSPARENT);
				SetBkMode(h_dc, TRANSPARENT);
				
				TextOut(h_dc, 10, 10, str, wcslen(str));
			}
			ReleaseDC(hWnd, h_dc);

		}
		*/
	}
	else if (uMsg == WM_DESTROY) { PostQuitMessage(0); }
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
