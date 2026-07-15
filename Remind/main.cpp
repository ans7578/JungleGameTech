#include <windows.h>


#pragma comment(lib, "user32")
#pragma	comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")


#include <d3d11.h>
#include <d3dcompiler.h>

#include "URenderer.h"

#include "Struct.h"


int WINAPI WndProc(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	return 0;
}

//각종 메시지를 처리할 함수
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
	return 0;
}



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	WCHAR	windowClass[] = L"JungleGameTech";

	WCHAR	Title[] = L"Game Tech Lab";
	
	/*
	UINT        style;
	WNDPROC     lpfnWndProc;
	int         cbClsExtra;
	int         cbWndExtra;
	HINSTANCE   hInstance;
	HICON       hIcon;
	HCURSOR     hCursor;
	HBRUSH      hbrBackground;
	LPCWSTR     lpszMenuName;
	LPCWSTR     lpszClassName;	
	*/

	WNDCLASSW wnd = {
		0,                  // style: 윈도우 스타일 (0 = 기본)
		WndProc,            // lpfnWndProc: 메시지 처리 콜백 함수
		0,                  // cbClsExtra: 추가 클래스 메모리
		0,                  // cbWndExtra: 추가 윈도우 메모리
		hInstance,          // hInstance: 프로그램 인스턴스
		nullptr,            // hIcon: 아이콘 (nullptr = 기본값)
		nullptr,            // hCursor: 커서 (nullptr = 기본값)
		nullptr,            // hbrBackground: 배경 브러시 (nullptr)
		nullptr,            // lpszMenuName: 메뉴 이름 (nullptr = 없음)
		windowClass         // lpszClassName: 윈도우 클래스 이름
	};
	RegisterClassW(&wnd);  // Windows에 클래스 등록


	

	bool bIsExit = false;

	HWND hwnd = CreateWindowExW(
		0,                                    // dwExStyle: 확장 스타일 (0 = 없음)
		windowClass,                          // lpClassName: 등록된 클래스 이름
		Title,                                // lpWindowName: 윈도우 제목
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,    // dwStyle: 스타일 (테두리+제목+표시)
		CW_USEDEFAULT, CW_USEDEFAULT,        // x, y: 위치 (자동)
		1024, 1024,                           // nWidth, nHeight: 크기 (1024x1024)
		nullptr,                              // hWndParent: 부모 윈도우 (없음)
		nullptr,                              // hMenu: 메뉴 (없음)
		hInstance,                            // hInstance: 인스턴스
		nullptr                               // lpParam: 추가 데이터
	);

	URenderer renderer;

	renderer.Create(hwnd);

	MSG msg = {};

	while (bIsExit == false)
	{
		while(PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			if (msg.message == WM_QUIT)
			{
				bIsExit = true;
				break;
			}
		}
	}

	renderer.ReleaseRasterizerState();
	renderer.ReleaseFrameBuffer();
	renderer.ReleaseDeviceAndSwapChain();

	return 0;
}

