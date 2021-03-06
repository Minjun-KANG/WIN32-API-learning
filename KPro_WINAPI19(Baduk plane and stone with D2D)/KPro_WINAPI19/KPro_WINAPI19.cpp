#include "KPro_WINAPI19.h"
#include "stdafx.h"

// Direct2D를 사용하기 위한 헤더 파일과 라이브러리 파일을 포함시킨다.
#include <d2d1.h>
#pragma comment(lib, "D2D1.lib")
// Direct2D에서 자주 사용할 네임 스페이스를 생략할 수 있도록 설정한다.
using namespace D2D1;

// 가로, 세로 줄이 19개인 바둑판을 만들어서 사용함
#define X_COUNT           19
#define Y_COUNT           19

// 화면의 왼쪽에서 바둑판의 왼쪽면까지의 거리(여백)
#define START_X           50
// 화면의 위쪽에서 바둑판의 위쪽면까지의 거리(여백)
#define START_Y           50

// 줄 사이의 간격이 26이다. 바둑 돌의 지름 크기도 동일하다.
#define INTERVAL          26
// 바둑 돌의 반지름은 줄 간격의 절반과 동일하다.
#define HALF_INTERVAL     INTERVAL/2

// 바둑판에 돌이 놓일 수 있는 위치를 좀더 편하게 계산할 수 있도록
// 매크로 함수로 만들었다. x와 y에 0 ~ 18 값을 사용하면 
// 실제 화면상의 좌표로 알 수 있다.
#define XPOS(x)   (float)(START_X + (x) * INTERVAL)
#define YPOS(y)   (float)(START_Y + (y) * INTERVAL)

// 바둑판에 돌이 놓여져 있는지 기억하기 위한 변수 배열의 각 항목의 값이 0이면 돌이 
// 놓여져 있지 않다는 뜻이고 1이면 검은색 돌, 2이면 흰색 돌이 놓여져 있다는 뜻이다.
unsigned char g_dol[Y_COUNT][X_COUNT];
// 현재 어떤 돌을 놓을 것인지를 결정하는 변수 (0이면 검은색, 1이면 흰색 돌을 놓을 순서)
unsigned char g_step;

// Direct2D를 구성하는 각종 객체를 생성하는 객체
ID2D1Factory *gp_factory;
// Direct2D에서 윈도우의 클라이언트 영역에 그림을 그릴 객체
ID2D1HwndRenderTarget *gp_render_target;

void OnPaint(HWND ah_wnd)
{
	// Direct2D의 Render Target을 사용해서 그림 그리기를 시작한다.
	gp_render_target->BeginDraw();
	// BeginDraw 함수를 사용하면 Render Target 전체 영역이 검은색으로 변경되기
	// 때문에 Clear 함수를 사용하여  윈도우 전체 영역을 갈색으로 채운다.
	gp_render_target->Clear(ColorF(0.95686f, 0.69f, 0.3019f));

	ID2D1SolidColorBrush *p_line_brush, *p_black_brush, *p_white_brush;
	// 선을 그리는데 사용할 Brush 객체를 생성한다.
	gp_render_target->CreateSolidColorBrush(ColorF(0.095686f, 0.069f, 0.03019f), &p_line_brush);
	gp_render_target->CreateSolidColorBrush(ColorF(0.0f, 0.0f, 0.0f), &p_black_brush);
	gp_render_target->CreateSolidColorBrush(ColorF(1.0f, 1.0f, 1.0f), &p_white_brush);

	D2D1_POINT_2F start_pos, end_pos;
	// 마우스 클릭 여부를 저장할 변수. 1이면 마우스가 클릭된 상태이고 0 이면 해제된 상태이다.
	for (int x = 0; x < X_COUNT; x++) {  // 수직으로 19개의 선을 그린다.
		start_pos.x = XPOS(x);
		start_pos.y = YPOS(0);
		end_pos.x = XPOS(x);
		end_pos.y = YPOS(Y_COUNT - 1);
		// (x, 0)점과 (x, Y_COUNT-1)점을 연결하는 선을 그린다.
		gp_render_target->DrawLine(start_pos, end_pos, p_line_brush, (float)1.0f);
	}

	for (int y = 0; y < Y_COUNT; y++) {   // 수평으로 19개의 선을 그린다.
		start_pos.x = XPOS(0);
		start_pos.y = YPOS(y);
		end_pos.x = XPOS(X_COUNT - 1);
		end_pos.y = YPOS(y);
		// (0, y)점과 (X_COUNT - 1, y)점을 연결하는 선을 그린다.
		gp_render_target->DrawLine(start_pos, end_pos, p_line_brush, (float)1.0f);
	}

	D2D1_ELLIPSE dol_region;
	dol_region.radiusX = (float)HALF_INTERVAL;  // 타원의 X축(수평)방향 반지름
	dol_region.radiusY = (float)HALF_INTERVAL;  // 타원의 Y축(수직)방향 반지름

	// 바둑판 전체에 놓여져 있는 돌을 각 위치별로 체크하면서 돌이 놓여져
	// 있으면 돌의 종류에 따라 그린다.
	for (int y = 0; y < Y_COUNT; y++) {
		for (int x = 0; x < X_COUNT; x++) {
			if (g_dol[y][x] > 0) {   // 바둑돌이 놓여져 있는 경우 (1:검은돌, 2:흰돌)
				dol_region.point.x = XPOS(x);
				dol_region.point.y = YPOS(y);
				// 검은돌이면 검은색을 설정하고 흰돌이면 흰색 타원을 그린다.
				// 이 타원은 (x,y)가 중심점이고 반지름이 HALF_INTERVAL이다.
				if (g_dol[y][x] == 1) gp_render_target->FillEllipse(dol_region, p_black_brush);
				else gp_render_target->FillEllipse(dol_region, p_white_brush);
			}
		}
	}

	p_line_brush->Release();
	p_line_brush = NULL;
	p_black_brush->Release();
	p_black_brush = NULL;
	p_white_brush->Release();
	p_white_brush = NULL;

	// Render Target을 사용해서 그림 그리기를 중지한다.
	gp_render_target->EndDraw();
}

void OnLButtonDown(HWND ah_wnd, int a_x, int a_y)
{
	// 바둑판 영역에만 돌을 놓을 수 있도록 터치한 위치가 바둑판 영역인지 체크한다.
	if (a_x > (XPOS(0) - HALF_INTERVAL) && a_y > (YPOS(0) - HALF_INTERVAL)
		&& a_x < (XPOS(X_COUNT - 1) + HALF_INTERVAL)
		&& a_y < (YPOS(Y_COUNT - 1) + HALF_INTERVAL)) {
		// 터치한 위치에 바둑판의 여백을 빼고 줄 간격으로 나누면 x, y 값이
		// 0 ~ 18의 값을 가지게 된다. 즉, 바둑판의 각 줄의 위치 값을 바로 
		// 얻을 수 있다. 그리고 터치한 위치와 가까운 줄쪽으로 이동할 수 있도록
		// 줄 간격의 절반만큼 더하고 줄간격으로 나누어야 한다. (블로그 설명 참고)
		int x = (a_x - START_X + HALF_INTERVAL) / INTERVAL;
		int y = (a_y - START_Y + HALF_INTERVAL) / INTERVAL;
		if (g_dol[y][x] == 0) {  // 돌이 없는 곳에만 돌을 놓을 수 있다.
								 // g_step이 0이면 검은돌이 놓여질 순서이고 1이면 흰돌이 놓여질 순서이기
								 // 때문에 g_step에 1을 더해서 바둑판에 놓여진 돌 정보를 구성하면
								 // 돌이 없으면 0, 검은돌이면 1, 흰돌이면 2가 저장됩니다.
			g_dol[y][x] = g_step + 1;
			// 검은돌을 놓았으면 흰돌로 상태를 변경하고 
			// 흰돌을 놓았으면 검은돌로 상태를 변경한다.
			g_step = !g_step;
			// 화면을 갱신해서 돌 놓은것을 적용한다.
			InvalidateRect(ah_wnd, NULL, TRUE);
		}
	}
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_PAINT) {
		ValidateRect(hWnd, NULL);  // WM_PAINT 메시지가 다시 발생하지 않게 만든다.
		OnPaint(hWnd);
		return 0;
	}
	else if (uMsg == WM_CREATE) {
		RECT r;
		GetClientRect(hWnd, &r);  // 클라이언트 영역의 좌표를 얻는다.
		// 지정한 윈도우의 클라이언트 영역에 그림을 그리기 위한 
		// Render Target을 생성한다.
		gp_factory->CreateHwndRenderTarget(RenderTargetProperties(),
			HwndRenderTargetProperties(hWnd, SizeU(r.right, r.bottom)),
			&gp_render_target);

		return 0;
	}
	else if (uMsg == WM_LBUTTONDOWN) {
		int x = LOWORD(lParam);    // 하위 16비트 값 분리, 마우스가 클릭된 X 좌표
		int y = HIWORD(lParam);    // 상위 16비트 값 분리, 마우스가 클릭된 Y 좌표
		OnLButtonDown(hWnd, x, y);
	}
	else if (uMsg == WM_DESTROY) PostQuitMessage(0);

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// 컴포넌트를 사용할 수 있도록 프로그램을 초기화한다.
	CoInitializeEx(NULL, COINIT_MULTITHREADED);
	// Direct2D를 위한 Factory 객체를 생성한다.
	if (S_OK != D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &gp_factory)) return 0;

	WNDCLASS wc;
	wchar_t my_class_name[] = L"KPro_WINAPI19";

	wc.cbClsExtra = NULL;
	wc.cbWndExtra = 0;
	// Direct2D를 사용해서 클라이언트 영역 전체를 그리기 때문에
	// 배경은 별도로 그리지 않아도 될 것 같아서 배경에 사용할 Brush 객체를 사용하지 않는다.
	wc.hbrBackground = (HBRUSH)NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = my_class_name;
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&wc);

	HWND h_wnd = CreateWindow(my_class_name, L"KPro_WINAPI19 - 오목 만들기! (D2D 사용)",
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, 50, 50, 600, 600, NULL, NULL, hInstance, NULL);

	ShowWindow(h_wnd, SW_SHOW);
	UpdateWindow(h_wnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	// 사용하던 Factory 객체를 제거한다.
	gp_factory->Release();
	// 컴포넌트 사용을 해제한다.
	CoUninitialize();
	return (int)msg.wParam;
}
