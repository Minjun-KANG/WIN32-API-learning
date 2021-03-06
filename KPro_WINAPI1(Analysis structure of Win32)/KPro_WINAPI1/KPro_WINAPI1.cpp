

#include "stdafx.h"
#include "KPro_WINAPI1.h"

//사용자가 메시지를 처리하는 함수


LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	/*CALLBACK은 함수의 포인터를 사용한다라는 개념이라,
	함수의 정의는 지켜야함 함수명은 변경가능
	*/
	/*
	if (uMsg == WM_DESTROY) {  //만약 x버튼을 누른다면
		//MessageBox(hWnd, L"안녕", L"메시지박스", MB_YESNO);
		//메시지박스 오너의 윈도우
		//메시지박스 내용
		//메시지박스 타이틀
		//메시지 박스에서 확인버튼 혹은 확인취소버튼과 같이 버튼을 관리 ex)MB_OK, MB_YESNO, MBOKCANCEL 등
		PostQuitMessage(0);
	}
	*/
	//이렇게 닫기에 대한 처리함수를 구성을 해놓지 않으면,
	/*
	닫기를 누르면 해당윈도우가 파괴되는데, 이때 아무런 작업이 없으면 문제가발생
	WinMain함수의 메세지처리루틴이 응답없음에 빠짐
	*/

	return DefWindowProc(hWnd, uMsg, wParam, lParam); //필수적인 기본처리 함수
	//프로그래머가 하고싶은 작업에 대한 내용
	//실질적으로 관리해야되는 공간
	
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//hInstance : 이 프로그램의 인스턴스 핸들값 전달
	//hPrevInstance : NULL
	//IpCmdLine : 명령행인자에 대한 포인터 cmd창으로 실행했을 때,
	//nCmdShow : 윈도우의 초기시작형식

	//윈도우 클래스 시작--
	WNDCLASS wc;

	wchar_t my_class_name[] = L"WINAPI1";
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
	//윈도우 클래스 등록완료!


	//윈도우 생성
	//WIN Main에서 생성한 윈도우는 MAIN윈도우라고 함

	HWND hWnd = CreateWindow(my_class_name, L"KPro_1_CLASS",
		WS_OVERLAPPEDWINDOW, 100, 90, 400, 350, NULL, NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);


	//프로그램에 전달된 메시지를 번역하고 실행하는 작업
	MSG msg; //읽어온 메시지를 저장할 구조체

	//다른 응용프로그램과 메시지를 주고받는 형식으로 진행
	//메시지 큐에서 순차적으로 데이터를 처리
	while (GetMessage(&msg, NULL, 0, 0)) { //메시지를 큐에서 읽는 함수
		TranslateMessage(&msg); //가상 키 메시지이면 ASCII 형태의 메시지(WM_CHAR)를 추가로 생성 //방향키
		DispatchMessage(&msg); //사용자의 메시지처리기인 WndProc함수를 호출
		/*
		어떻게 사용자함수를 처리하지? 표준함수가?
		WNDCALSS를 만들때
		lpfnWndProc에 WndProc함수의 주소를 넘겨줘서 가능
		*/

		//PostQuitMessage(0);
	}

	/* --MSG 구조체

	typedef struct tagMSG
	{
		HWND hwnd;		 //메시지가 발생한 윈도우 핸들
		UINT message;	//발생한 메시지 아이디
		WPARAM wParam; //메시지와 함께 전달된 32bit 데이터 (과거16)
		LPARAM lParam;	 //메시지와 함께 전달된 16bit 데이터
		DWORD time;		//메시지가 전달된 시간(초단위 값)
		POINT pt;	   //메시지가 전달 되었을 때의 마우스 커서 좌표값
	}MSG;
	*/

	/*
	GetMessage(&msg, NULL, 0, 0) 함수란?
	실행 -> 0이 아닌값을 반환 -> 처리
	종료 -> 0을 반환 -> while문 종료 -> winmain종료 -> 프로그램종료
	WM_QUIT 메시지가 수신되어 0값을 반환

	PostQuitMessage(0)을 넣으면 도중종료가능

	*/
	
	return msg.wParam;
}

