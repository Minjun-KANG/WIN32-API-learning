// 실습 바둑판
#include "stdafx.h"
#include "KPro_WINAPI7-1(실습).h"
#include<windowsx.h>

void OnPaint(HWND ah_wnd); //바둑판을 그리는 함수
void OnLButtonDown(HWND, int, int); //왼쪽버튼을 눌렀을 때, 처리하는 함수

// 19*19 바둑판
#define X_COUNT 19
#define Y_COUNT 19

// 바둑판이 그려질 시작좌표
#define START_X 50
#define START_Y 50

//각 칸의 폭(줄 사이의 간격)
#define INTERVAL 26

//바둑돌의 반지름
#define HALF_INTERVAL INTERVAL/2

//바둑판에 돌이 놓일 수 있는 위치좌표를 매크로로
#define XPOS(x) (START_X + (x) * INTERVAL)
#define YPOS(y) (START_Y + (y) * INTERVAL)


//바둑판에 돌이 놓여져 있는지 기억하는 배열
//0이면 없고 1이면 흑돌, 2면 백돌
unsigned char g_dol[X_COUNT][Y_COUNT];

//현재 어떤 돌을 놓을 것인지 결정하는, (0이면 흑돌, 1이면 백돌)
unsigned char g_step;
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_PAINT)
	{
		OnPaint(hWnd); //WM_PAINT 메시지처리
		return 0;
	}
	if (uMsg == WM_LBUTTONDOWN)
	{
		int x = GET_X_LPARAM(lParam);
		int y = GET_Y_LPARAM(lParam);
		OnLButtonDown(hWnd, x, y);
	}
	if (uMsg == WM_DESTROY) { PostQuitMessage(0); }
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASS wc;
	HBRUSH h_bk_brush = CreateSolidBrush(RGB(244, 176, 77)); //배경색 지정

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
		WS_OVERLAPPEDWINDOW, 50, 50, 600, 600, NULL, NULL, hInstance, NULL); //windows의 생성 x,y,  폭,넓이
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


void OnPaint(HWND ah_wnd)
{
	PAINTSTRUCT ps;
	HDC h_dc = BeginPaint(ah_wnd, &ps);
	

	for (int x = 0; x < X_COUNT; x++) //수직으로 19개의 선을 그림
	{	//x,0과 x,18까지 쭉 그림
		MoveToEx(h_dc, XPOS(x), YPOS(0), NULL);
		LineTo(h_dc, XPOS(x), YPOS(Y_COUNT - 1));
	}

	for (int y = 0; y < Y_COUNT; y++)	//수평으로 19개의 선을 그림
	{	//0,y부터 18,y까지 쭉 그림
		MoveToEx(h_dc, XPOS(0), YPOS(y), NULL);
		LineTo(h_dc, XPOS(X_COUNT - 1), YPOS(y));
	}

	for (int y = 0; y < Y_COUNT; y++) 
	{
		for (int x = 0; x < X_COUNT; x++)
		{
			if (g_dol[y][x] > 0) //1흑돌, 2백돌 이 놓여져 있는 경우
			{
				if (g_dol[y][x] == 1) //흑돌이면
				{
					SelectObject(h_dc, GetStockObject(BLACK_BRUSH)); // 검은색을 채운다
				}
				else {
					SelectObject(h_dc, GetStockObject(WHITE_BRUSH)); // 흰색을 채운다.
				}
				//원을 그린다. (x,y)를 중심점으로, HALF_INTERVAL을 반지름으로
				Ellipse(h_dc, XPOS(x) - HALF_INTERVAL, YPOS(y) - HALF_INTERVAL,
					XPOS(x) + HALF_INTERVAL, YPOS(y) + HALF_INTERVAL);
			}
		}
	}
	EndPaint(ah_wnd, &ps);
}

void OnLButtonDown(HWND ah_wnd, int a_x, int a_y)
{
	//바둑판 영역인지 판단
	if (a_x > (XPOS(0) - HALF_INTERVAL) && a_y > (YPOS(0) - HALF_INTERVAL)
		&& a_x < (XPOS(X_COUNT - 1) + HALF_INTERVAL)
		&& a_y < (YPOS(Y_COUNT - 1) + HALF_INTERVAL))
	{// 돌 놓을 작업

		// HDC h_dc = GetDC(ah_wnd);




	/*	int x = (a_x - START_X + HALF_INTERVAL) / INTERVAL;
		int y = (a_y - START_Y + HALF_INTERVAL) / INTERVAL;*/
		int x = (a_x - START_X) / INTERVAL;
		int y = (a_y - START_Y) / INTERVAL;
		
		if (g_dol[y][x] == 0) //돌이 없는 곳에만 착수가능
		{
			g_dol[y][x] = g_step + 1; //[y][x]의 값에 g_step+1을 넣음
			/* 
			gstep이 0이면 검은돌, 1이면 흰돌이 놓여질 순서
			때문에 g_step에 1을 더해버림
			그러면 검은돌이면 step이  0 일때 1이 들어가서 1인 검은돌이 나오는 원리
			*/
			g_step = !g_step; // 여기서 g_step의 값을 반전
			InvalidateRect(ah_wnd, NULL, TRUE); //WM_PAINT 호출
		}




		/*x = x * INTERVAL + START_X;
		y = y * INTERVAL + START_Y;*/

		/*Ellipse(h_dc, x - HALF_INTERVAL, y - HALF_INTERVAL, x + HALF_INTERVAL, y + HALF_INTERVAL);
		ReleaseDC(ah_wnd, h_dc);*/

	}

}