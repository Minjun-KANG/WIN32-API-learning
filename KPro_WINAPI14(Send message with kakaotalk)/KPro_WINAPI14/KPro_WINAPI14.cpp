#include "stdafx.h"
#include "KPro_WINAPI14.h"
#include<windowsx.h>
#include<string.h>


LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	if (uMsg == WM_LBUTTONDOWN)
	{
		{
			HWND h_find_wnd = NULL;

			while (h_find_wnd = FindWindowEx(NULL, h_find_wnd, L"#32770", NULL))
			{
				HWND h_edit_wnd = FindWindowEx(h_find_wnd, NULL, L"RichEdit20W", NULL);
				if (h_edit_wnd)
				{
					//톡방을 찾음!
					SendMessage(h_edit_wnd, WM_SETTEXT, NULL, (LPARAM)L"안녕하세요");
					
					Sleep(10);
					PostMessage(h_edit_wnd, WM_KEYDOWN, 0x0000000D, 0x001C0001); // 지금메세지는 지나가고, 다음 메시지를 보내겠다. send랑 겹칠까봐(동기식)
					PostMessage(h_edit_wnd, WM_KEYUP, 0x0000000D, 0xC01C0001);

					break;
				}
			}
			
		}
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

