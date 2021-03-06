#include "stdafx.h"
#include "KPro_WINAPI16.h"
#include<windowsx.h>
#include<string.h>

#define MAX_COUNT 30 //30개 단톡방까지 정의

typedef struct TalkWnd
{
	//카톡방 윈도우, 에디트 윈도우
	HWND h_talk_wnd, h_edit_wnd;
	//카톡방 제목
	wchar_t title[256];

}TALKWND;

TALKWND g_talk_list[MAX_COUNT];
int g_talk_conut = 0;

//채팅을 입력할 에디트컨트롤의 핸들을 저장 , 전송버튼 핸들을 만듦
HWND gh_chat_edit, gh_send_btn;
HWND gh_list_box;
HFONT gh_font;

void FindTalkWindow(); //윈도우 상에 카톡방을 찾는다
void SendChatData(); // 데이터를 카톡방에 전송한다



LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_CREATE)
	{
		gh_font = CreateFont(12, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0,
			DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
			DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"굴림체");

		gh_chat_edit = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", NULL,
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
			5, 303, 532, 28, hWnd, (HMENU)25002, NULL, NULL);

		SendMessage(gh_chat_edit, WM_SETFONT, (WPARAM)gh_font, 1);

		gh_send_btn = CreateWindow(L"Button", L"전송",
			WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
			540, 301, 80, 31, hWnd, (HMENU)25003, NULL, NULL);
		SendMessage(gh_send_btn, WM_SETFONT, (WPARAM)gh_font, 1);
		
		gh_list_box = CreateWindowEx(WS_EX_CLIENTEDGE, L"ListBox", NULL,
			WS_CHILD | WS_VISIBLE | LBS_STANDARD,
			5, 5, 615, 300, hWnd, (HMENU)25001, NULL, NULL);
		SendMessage(gh_list_box, WM_SETFONT, (WPARAM)gh_font, 1);

		FindTalkWindow();
		return 0;
	}
	else if (uMsg == WM_DESTROY)
	{
		DestroyWindow(gh_chat_edit);
		DestroyWindow(gh_send_btn);
		DestroyWindow(gh_list_box);
		DeleteObject(gh_font);
		PostQuitMessage(0);
	}
	else if (uMsg == WM_COMMAND) //wparam에 하위 16bit에 커맨드를 발생시킨 컨트롤에 ID가 넘어옴
	{
		if (LOWORD(wParam) == 25003)
		{
			SendChatData();
		}
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
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
		50, 50, 640, 374, NULL, NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

void FindTalkWindow()
{
	HWND h_find_wnd = 0;
	TALKWND *p = g_talk_list;

	wchar_t str[256];

	while (h_find_wnd = FindWindowEx(NULL, h_find_wnd, L"#32770", NULL))
	{
		p->h_edit_wnd = FindWindowEx(h_find_wnd, NULL, L"RichEdit20W", NULL);

		if (p->h_edit_wnd)
		{
			p->h_talk_wnd = h_find_wnd;

			GetWindowText(p->h_talk_wnd, p->title, 256);
			swprintf(str, 256, L"카톡방 확인 : %s", p->title);
			SendMessage(gh_list_box, LB_INSERTSTRING, g_talk_conut, (LPARAM)str);
			p++;
			g_talk_conut++;
		}
	}
}
void SendChatData()
{
	if (g_talk_conut == 0) return;



	wchar_t str[128];
	GetWindowText(gh_chat_edit, str, 128);
	TALKWND *p = g_talk_list;
	int index = SendMessage(gh_list_box, LB_INSERTSTRING, -1, (LPARAM)str); // 가장 뒤쪽으로 들어갈 수 있게함 -1

	SendMessage(gh_list_box, LB_SETCURSEL, index, 0); //커서 자동설정

	for (int i = 0; i < g_talk_conut; i++) {
		SendMessage(p[i].h_edit_wnd, WM_SETTEXT, NULL, (LPARAM)str);
	}

	Sleep(200);

	for (int i = 0; i < g_talk_conut; i++) {
		
		PostMessage(p[i].h_edit_wnd, WM_KEYDOWN, 0x0000000D, 0x001C0001); // 지금메세지는 지나가고, 다음 메시지를 보내겠다. send랑 겹칠까봐(동기식)
		PostMessage(p[i].h_edit_wnd, WM_KEYUP, 0x0000000D, 0xC01C0001);
	}

	SetWindowText(gh_chat_edit, L"");
}	