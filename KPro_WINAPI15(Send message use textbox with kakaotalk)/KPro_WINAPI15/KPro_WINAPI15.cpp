#include "stdafx.h"
#include "KPro_WINAPI15.h"
#include<windowsx.h>
#include<string.h>


//카톡방 윈도우, 에디트 윈도우
HWND gh_talk_wnd, gh_edit_wnd;

//채팅을 입력할 에디트컨트롤의 핸들을 저장 , 전송버튼 핸들을 만듦
HWND gh_chat_edit, gh_send_btn;
void FindTalkWindow()
{
	
	while (gh_talk_wnd = FindWindowEx(NULL, gh_talk_wnd, L"#32770", NULL))
	{
		gh_edit_wnd = FindWindowEx(gh_talk_wnd, NULL, L"RichEdit20W", NULL);
		if (gh_edit_wnd)
		{
			break;
		}
	}
}

void SendChatData()
{
	if (!gh_edit_wnd) return;

	wchar_t str[128];
	GetWindowText(gh_chat_edit, str, 128);

	SendMessage(gh_edit_wnd, WM_SETTEXT, NULL, (LPARAM)str);

	Sleep(200);
	PostMessage(gh_edit_wnd, WM_KEYDOWN, 0x0000000D, 0x001C0001); // 지금메세지는 지나가고, 다음 메시지를 보내겠다. send랑 겹칠까봐(동기식)
	PostMessage(gh_edit_wnd, WM_KEYUP, 0x0000000D, 0xC01C0001);


}
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_CREATE)
	{
		gh_chat_edit = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", NULL, 
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
			5, 303, 532, 28, hWnd, (HMENU)25002, NULL, NULL);

		gh_send_btn = CreateWindow(L"Button", L"전송",
			WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
			540, 301, 80, 31, hWnd, (HMENU)25003, NULL, NULL);

		FindTalkWindow();
		return 0;
	}
	else if (uMsg == WM_DESTROY) 
	{ 
		DestroyWindow(gh_chat_edit);
		DestroyWindow(gh_send_btn);
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

