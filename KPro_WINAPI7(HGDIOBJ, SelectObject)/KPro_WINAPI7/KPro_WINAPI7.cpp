#include "stdafx.h"
#include "KPro_WINAPI7.h"
#include<windowsx.h>


LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	/*
	if (uMsg == WM_LBUTTONDOWN)
	{
		HDC h_dc = GetDC(hWnd); //dc얻고
		SelectObject(h_dc, GetStockBrush(DC_BRUSH)); //dc중 brush객체의 속성을 DC_BRUSH로 바꿈
		SetDCBrushColor(h_dc, RGB(255, 100, 100)); //DC_BRUSH라는 기본속성의 값을 바꿔사용
		Rectangle(h_dc, 10, 10, 50, 50); //사각형출력
		ReleaseDC(hWnd, h_dc); //릴리즈하는순간 h_dc안에있는 색상은 날라감
	}*/
	/*
	if (uMsg == WM_LBUTTONDOWN)
	{
		HDC h_dc = GetDC(hWnd);
		
		SelectObject(h_dc, GetStockObject(GRAY_BRUSH)); 
		
		Rectangle(h_dc, 50, 50, 100, 100);

		ReleaseDC(hWnd, h_dc);
	}*/
	
	/*
	if (uMsg == WM_LBUTTONDOWN)
	{
		HDC h_dc = GetDC(hWnd);
		HPEN h_pen;

		//pen의 속성을 비교하기위한 출력문자열과, 속성인자값을 배열로 선언
		const char *p_style_string[6] = { "PS_SOLID","PS_DASH","PS_DOT","PS_DASHDOT","PS_DASHDOTDOT","PS_NULL" };

		//const char *p_style_string[6] = { L"PS_SOLID",L"PS_DASH",L"PS_DOT",L"PS_DASHDOT",L"PS_DASHDOTDOT",L"PS_NULL" }; 유니코드용
		int pen_style[6] = { PS_SOLID,PS_DASH , PS_DOT , PS_DASHDOT , PS_DASHDOTDOT , PS_NULL };
		
		//점선의 경우 점과 점사의의 색이 배경색으로 출력되지 않도록, 배경을 투명하게 하는 옵션
		SetBkMode(h_dc, TRANSPARENT);
		//SetBkColor(h_dc, RGB(0, 255, 0));
		HGDIOBJ	h_old_pen = GetCurrentObject(h_dc, OBJ_PEN); //현재 pen객체의 핸들값을 얻음
		//HPEN h_old_pen = SelectObject(h_dc, h_brush) 로 했던것을 위처럼 함 for문 안에있으면 Release를 두번씩해줘야함

		for (int i = 0; i < 6; i++)
		{
			//문자열을 출력 
			TextOutA(h_dc, 10, 10 + i * 20, p_style_string[i], strlen(p_style_string[i]));
			//TextOut(h_dc, 10, 10 + i * 20, p_style_string[i], wcslen(p_style_string[i])); 유니코드용
			h_pen = CreatePen(pen_style[i], 1, RGB(0, 0, 255)); //점선은 선 굵기가 1이여야 한다.

			SelectObject(h_dc, h_pen);

			MoveToEx(h_dc, 200, 15 + i * 20, NULL);
			LineTo(h_dc, 400, 15 + i * 20);

			DeleteObject(h_pen);

		}

		SelectObject(h_dc, h_old_pen);

		ReleaseDC(hWnd, h_dc);
	}*/
	/*
	if (uMsg == WM_LBUTTONDOWN)
	{
		HDC h_dc = GetDC(hWnd);

		HPEN h_pen = CreatePen(PS_SOLID,3, RGB(255, 0, 0)); //타입, 굵기, 색상


		HGDIOBJ h_old_pen = SelectObject(h_dc, h_pen); // h_dc에 있던 값을  h_brush로 교체, *h_brush를 h_dc에 넣음) (h_dc를 old에 넣음)

		Rectangle(h_dc, 50, 50, 100, 100);

		MoveToEx(h_dc, 200, 200, NULL);
		LineTo(h_dc, 300, 200);

		SelectObject(h_dc, h_pen); //DeleteObject 하기전에 다시 바꿔주고

		DeleteObject(h_pen); //지움
		DeleteObject(h_old_pen);

		ReleaseDC(hWnd, h_dc);
	}
	*/
	
	if (uMsg == WM_LBUTTONDOWN)
	{
		HDC h_dc = GetDC(hWnd);
		HBRUSH h_brush = CreateSolidBrush(RGB(0, 0, 255));


		HGDIOBJ h_old_brush = SelectObject(h_dc, h_brush); // h_dc에 있던 값을  h_brush로 교체, *h_brush를 h_dc에 넣음) (h_dc를 old에 넣음)
		//HBRUSH h_old_brush = (HBRUSH)SelectObject(h_dc, h_brush); 같게동작

		Rectangle(h_dc, 50, 50, 100, 100);
		
		SelectObject(h_dc, h_old_brush); //DeleteObject 하기전에 다시 바꿔주고,

		Rectangle(h_dc, 250, 50, 300, 100); //바뀜을 증명
		

		DeleteObject(h_brush); //지움
		DeleteObject(h_old_brush);

		ReleaseDC(hWnd, h_dc);
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

