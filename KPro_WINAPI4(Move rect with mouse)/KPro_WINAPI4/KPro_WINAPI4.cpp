#include "stdafx.h"
#include "KPro_WINAPI4.h"
#include<windowsx.h>


int g_is_click = 0;
RECT g_rect = { 10,10,50,50 }; //Step2
POINT g_prev_pos;


LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	if (uMsg == WM_PAINT)
	{
		PAINTSTRUCT ps;
		HDC h_dc = BeginPaint(hWnd, &ps);
		Rectangle(h_dc, g_rect.left, g_rect.top, g_rect.right, g_rect.bottom); //Step1 - Rect 구조체를 생성해서 편하게!
	
		EndPaint(hWnd, &ps);
		return 0;
	}
	else if (uMsg == WM_LBUTTONDOWN)
	{
		//Step5 - 마우스포인터의 이전좌표를 전역변수로!
		g_prev_pos.x = GET_X_LPARAM(lParam);
		g_prev_pos.y = GET_Y_LPARAM(lParam);

		//Step4 -- step3의 if문을 처리
		if (PtInRect(&g_rect, g_prev_pos )) //마우스 포인터가 사각형안에 있는가? 라는 함수
		{
			g_is_click = 1;
			SetCapture(hWnd); //이 Window가 마우스를 점유해버리겠다. Step10;
		}

		/*
		
		int x = GET_X_LPARAM(lParam);
		int y = GET_Y_LPARAM(lParam);
		
		Step3 -- 해당 if문과 같게
		//사각형 안에 마우스포인터가 있는가?
		if (x >= g_rect.left && x <= g_rect.right && y >= g_rect.top && y <= g_rect.bottom)
		{
			g_is_click = 1; //예 있습니다.
		}*/
	}
	else if (uMsg == WM_LBUTTONUP)
	{
		g_is_click = 0;
		ReleaseCapture(); //Window가 마우스 점유를 그만두겠다
	}
	else if (uMsg == WM_MOUSEMOVE) {
		if (g_is_click)
		{
			/*
			//Step6 -- 위치를 가지고 놀자!
			HDC h_dc = GetDC(hWnd);

			//처음클릭과 나중클릭을 빼면 마우스 이동거리가 되는데,
			//그 좌표를 기억한다.
			
			POINT pos = { GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam) }; //현재 마우스좌표 기억변수

			//현재 위치에서 이전위치 를 뺌
			int h_interval = pos.x - g_prev_pos.x; 
			int v_interval = pos.y - g_prev_pos.y;

			// 사각형을 바꿔줌
			g_rect.left += h_interval;
			g_rect.top += v_interval;
			g_rect.right += h_interval;
			g_rect.bottom += v_interval;

			Rectangle(h_dc, g_rect.left, g_rect.top, g_rect.right, g_rect.bottom);
			
			// 이렇지 않으면 최초의 값으로 계산함
			//g_prev_pos.x = pos.x;
			//g_prev_pos.y = pos.y;
			
			ReleaseDC(hWnd, h_dc);
			*/
			
		

			//Step7 - 좌표만 계산으로 바꾸자!
			POINT pos = { GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam) };

			//Step8 - 밑에 h_interval 코드를 OffsetRect를 이용하라
			OffsetRect(&g_rect, pos.x - g_prev_pos.x, pos.y - g_prev_pos.y);
			/*
			//현재 위치에서 이전위치 를 뺌
			int h_interval = pos.x - g_prev_pos.x;
			int v_interval = pos.y - g_prev_pos.y;

			// 사각형을 바꿔줌
			g_rect.left += h_interval;
			g_rect.top += v_interval;
			g_rect.right += h_interval;
			g_rect.bottom += v_interval;
			*/
			g_prev_pos.x = pos.x;
			g_prev_pos.y = pos.y;


			InvalidateRect(hWnd, NULL, TRUE); //전체 영역 -> NULL, 배경 새로 그려라->TRUE //간접적으로 WM_PAINT메시지를 발생 Step9
			
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

