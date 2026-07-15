#include <windows.h>


#pragma comment(lib, "user32")
#pragma	comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")


#include <d3d11.h>
#include <d3dcompiler.h>

#include "URenderer.h"

#include "Struct.h"

//메시지를 처리하는 콜백함수
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	WCHAR WindowClassName[] = L"JungleWindowClass";

	WCHAR Title[] = L"Game Tech Lab";


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

	WNDCLASSW wndClass = { 0, WndProc,0,0,0,0,0,0,0, WindowClassName };

	RegisterClassW(&wndClass);

	// 1024 x 1024 크기에 윈도우 생성
	HWND hWnd = CreateWindowExW(0, WindowClassName, Title, WS_POPUP | WS_VISIBLE | WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 1280, 720,
		nullptr, nullptr, hInstance, nullptr);


	bool bIsExit = false;

	URenderer renderer;

	renderer.Create(hWnd);

	// Renderer와 Shader 생성 이후에 버텍스 버퍼를 생성합니다.
	FVertexSimple* vertices = triangle_vertices;
	UINT ByteWidth = sizeof(triangle_vertices);
	UINT numVertices = sizeof(triangle_vertices) / sizeof(FVertexSimple);

	// 생성
	D3D11_BUFFER_DESC vertexbufferdesc = {};
	vertexbufferdesc.ByteWidth = ByteWidth;
	vertexbufferdesc.Usage = D3D11_USAGE_IMMUTABLE;
	vertexbufferdesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA vertexbufferSRD = { vertices };

	ID3D11Buffer* vertexBuffer;

	renderer.Device->CreateBuffer(&vertexbufferdesc, &vertexbufferSRD, &vertexBuffer);




	while (bIsExit == false)
	{
		MSG msg;

		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			//키입력 메시지를 번역
			TranslateMessage(&msg);

			// 메시지를 적절한 윈도우 프로시저에 전달, 메시지가 위에서 등록한 WndProc 으로 전달됨
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT)
			{
				bIsExit = true;
				break;
			}
		}
		renderer.Preapre();
		renderer.PrepareShader();


		renderer.RenderPrimitive(vertexBuffer, numVertices);

		
		renderer.SwapBuffer();
	}

	renderer.Release();

	return 0;
}






