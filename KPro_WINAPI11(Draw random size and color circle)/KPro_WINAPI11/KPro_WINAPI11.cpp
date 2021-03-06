/*
rand
*/
#include "stdafx.h"
#include "KPro_WINAPI11.h"
#include<windowsx.h>

//Random//////
#include<time.h>
#include<stdlib.h>


typedef struct Circle
{
	int x;
	int y;
	int r;
	COLORREF color;
}CIRCLE;
#define MAX_COUNT 100





CIRCLE g_pos[MAX_COUNT];
void MakeCircle(CIRCLE *, RECT *);

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_PAINT)
	{
		PAINTSTRUCT ps;
		HDC h_dc = BeginPaint(hWnd, &ps);
		CIRCLE *p = g_pos;
		HBRUSH h_brush;
		HGDIOBJ h_old_brush = GetCurrentObject(h_dc, OBJ_BRUSH); //기존 값을 가진다.

		for (int i = 0; i < MAX_COUNT; i++)
		{
			/*Ellipse(h_dc, g_pos[i].x - g_pos[i].r, g_pos[i].y - g_pos[i].r,
				g_pos[i].x + g_pos[i].r, g_pos[i].y + g_pos[i].r); */
			
			h_brush = CreateSolidBrush(p->color);
			SelectObject(h_dc, h_brush);
			Ellipse(h_dc, p->x - p->r, p->y - p->r, p->x + p->r, p->y + p->r);
			p++;
			DeleteObject(h_brush);
		}

		SelectObject(h_dc, h_old_brush);
		EndPaint(hWnd, &ps);
		return 0;
	}
	else if (uMsg == WM_TIMER)
	{/*
		if (wParam == 1)
		{
			for (int i = 0; i < MAX_COUNT; i++)
			{
				g_pos[i].r--;
				if (g_pos[i].r <= 1)
				{
					RECT r;
					GetClientRect(hWnd, &r);

					MakeCircle(&g_pos[i], &r);
					
				}
			}
			InvalidateRect(hWnd, NULL, TRUE);

		}*/
	}
	else if (uMsg == WM_CREATE)
	{
		SetTimer(hWnd, 1, 50,NULL);

		srand((unsigned int)time(NULL));
		RECT rect;
		GetClientRect(hWnd, &rect); //Client 크기를 가져온다

		for (int i = 0; i < MAX_COUNT; i++)
		{
			MakeCircle(g_pos + i, &rect);
			/*
			g_pos[i].x = rand() % rect.right;
			g_pos[i].y = rand() % rect.bottom;
			g_pos[i].r = rand() % 50 + 10; //10~59
			g_pos[i].color = RGB(rand() % 256, rand() % 256, rand() % 256);
			*/
		}

		return 0;
	}
	else if (uMsg == WM_DESTROY) 
	{
		KillTimer(hWnd, 1);
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

void MakeCircle(CIRCLE *ap_data, RECT *ap_rect)
{
	ap_data->x = rand() % ap_rect->right;
	ap_data->y = rand() % ap_rect->bottom;
	ap_data->r = rand() % 50 + 10; //10~59
	//ap_data->color = RGB(rand() % 256, rand() % 256, rand() % 256);
	ap_data->color = RGB(0, 0, rand() % 256);

}

