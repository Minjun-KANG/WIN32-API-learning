/*
rand
*/
#include "stdafx.h"
#include "KPro_WINAPI12.h"
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
void DrawEllipse(HDC);
RECT g_rect;


HDC gh_mem_dc; //새로운 "메모리상" DC생성 //초기값으로 폭과 높이가 1인 bmp를 가지고 있음
HBITMAP gh_mem_bmp; //DC에 비트맵핸들을 연결하기 위함 //따라서 원하는 크기의 bitmap을 만듬



LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_PAINT)
	{
		PAINTSTRUCT ps;
		HDC h_dc = BeginPaint(hWnd, &ps);

		BitBlt(h_dc, 0, 0, g_rect.right, g_rect.bottom, gh_mem_dc, 0, 0, SRCCOPY);


		
		
		EndPaint(hWnd, &ps);
		return 0;
	}
	else if (uMsg == WM_TIMER)
	{
		if (wParam == 1)
		{
			for (int i = 0; i < MAX_COUNT; i++)
			{
				g_pos[i].r--;
				if (g_pos[i].r <= 1)
				{

					MakeCircle(&g_pos[i], &g_rect);

				}
			}

			DrawEllipse(gh_mem_dc);
			InvalidateRect(hWnd, NULL, FALSE);

		}
	}
	else if (uMsg == WM_CREATE)
	{
		SetTimer(hWnd, 1, 50, NULL);
		GetClientRect(hWnd, &g_rect); //Client 크기를 가져온다
		srand((unsigned int)time(NULL));

		HDC h_dc = GetDC(hWnd);

		gh_mem_dc = CreateCompatibleDC(h_dc); //기존에 있는 dc의 값을 복제한다.
		gh_mem_bmp = CreateCompatibleBitmap(h_dc, g_rect.right, g_rect.bottom);
		SelectObject(gh_mem_dc, gh_mem_bmp); 

		ReleaseDC(hWnd, h_dc);

		for (int i = 0; i < MAX_COUNT; i++)
		{
			MakeCircle(g_pos + i, &g_rect);
		}
		
		return 0;
	}
	else if (uMsg == WM_SIZE)
	{
		GetClientRect(hWnd, &g_rect);
		if (gh_mem_bmp != NULL) {
			DeleteObject(gh_mem_bmp);
		}
		HDC h_dc = GetDC(hWnd);
		
		gh_mem_bmp = CreateCompatibleBitmap(h_dc, g_rect.right, g_rect.bottom);
		SelectObject(gh_mem_dc, gh_mem_bmp);
		FillRect(gh_mem_dc, &g_rect, (HBRUSH)GetStockObject(WHITE_BRUSH));
		ReleaseDC(hWnd, h_dc);
	}
	else if (uMsg == WM_DESTROY)
	{
		KillTimer(hWnd, 1);
		DeleteObject(gh_mem_dc);
		DeleteObject(gh_mem_bmp);
		PostQuitMessage(0);
	}
	
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASS wc;
	HBRUSH h_bk_brush = CreateSolidBrush(RGB(244, 0, 0)); //배경색 지정

	wchar_t my_class_name[] = L"KPro_WINAPI";
	wc.cbClsExtra = NULL;
	wc.cbWndExtra = NULL;
	wc.hbrBackground = h_bk_brush;
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
	DeleteObject(h_bk_brush);
	return msg.wParam;
}

void MakeCircle(CIRCLE *ap_data, RECT *ap_rect)
{
	ap_data->x = rand() % ap_rect->right;
	ap_data->y = rand() % ap_rect->bottom;
	ap_data->r = rand() % 50 + 10; //10~59
	ap_data->color = RGB(rand() % 256, rand() % 1, rand() % 1);
	

}
void DrawEllipse(HDC ah_dc)
{
	CIRCLE *p = g_pos;
	HBRUSH h_brush;
	HGDIOBJ h_old_brush = GetCurrentObject(ah_dc, OBJ_BRUSH); //기존 값을 가진다.
	HGDIOBJ h_old_pen = SelectObject(ah_dc, GetStockObject(NULL_PEN)); //펜 날림
	FillRect(ah_dc, &g_rect, (HBRUSH)GetStockObject(WHITE_BRUSH));

	for (int i = 0; i < MAX_COUNT; i++)
	{
		h_brush = CreateSolidBrush(p->color);
		SelectObject(ah_dc, h_brush);
		Ellipse(ah_dc, p->x - p->r, p->y - p->r, p->x + p->r, p->y + p->r);
		p++;
		DeleteObject(h_brush);
	}
	SelectObject(ah_dc, h_old_pen);
	SelectObject(ah_dc, h_old_brush);
}

