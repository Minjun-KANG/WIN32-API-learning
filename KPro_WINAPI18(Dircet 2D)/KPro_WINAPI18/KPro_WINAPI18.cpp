#include "stdafx.h"
#include "KPro_WINAPI18.h"
#include<windowsx.h>

#include<d2d1.h> //헤더 추가
#pragma comment(lib,"D2D1.lib") //라이브러리 추가

//네임스페이스를 생략할 수 있도록,
using namespace D2D1;

//D2를 구성하는 각종객체를 생성하는 객체
ID2D1Factory *gp_factory;

//D2에서 윈도우 클라이언트 영역에 그림을 그릴 객체
ID2D1HwndRenderTarget *gp_render_target;


LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_PAINT)
	{
		ValidateRect(hWnd, NULL);	//WM_PAINT 재발생 금지시킴

		//D2에 Render_target을 사용하여 그림그리기를 시작;
		gp_render_target->BeginDraw();

		//배경을 0.0, 0.8, 1.0 의 색으로 설정 // 하늘색
		gp_render_target->Clear(ColorF(0.0f, 0.8f, 1.0f));


		D2D1_ELLIPSE my_region;

		//타원의 중심점을 100,100 설정
		my_region.point.x = 100;
		my_region.point.y = 100;
		my_region.radiusX = 50.0f;
		my_region.radiusY = 50.0f;

		//yellow_brush 라는 ID2D1 Brush 타입의 객체를 생성,
		ID2D1SolidColorBrush *p_yellow_brush = NULL;
		

		//BRUSH 객체를 노란색으로 만듬
		gp_render_target->CreateSolidColorBrush(ColorF(1.0f, 1.0f, 0.0f), &p_yellow_brush);


		//색상을 p_yellow_brush 안에 있는 걸로 채워서, 원 형태를 my_region에서 가져와 출력
		gp_render_target->FillEllipse(my_region, p_yellow_brush);

		p_yellow_brush->Release();
		p_yellow_brush = NULL;

		
		



		//그림그림을 종료

		gp_render_target->EndDraw();
		
		return 0;
	}
	if (uMsg == WM_CREATE)
	{
		RECT r;
		GetClientRect(hWnd, &r);

		//Render target 설정
		gp_factory->CreateHwndRenderTarget(RenderTargetProperties(), 
			HwndRenderTargetProperties(hWnd, SizeU(r.right, r.bottom)),
			&gp_render_target);
		return 0;
	}
	else if (uMsg == WM_DESTROY)
	{
		if (gp_render_target)
		{
			gp_render_target->Release();
			gp_render_target = NULL;
		}
		PostQuitMessage(0);
	}
	return(DefWindowProc(hWnd, uMsg, wParam, lParam));
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	//컴포넌트를 사용할 수 있도록 프로그램을 초기화;
	CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);

	//D2를 위한 Factory 객체생성

	D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &gp_factory);

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
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
		50, 50, 640, 374, NULL, NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	gp_factory->Release();
	CoUninitialize();

	return msg.wParam;
}

