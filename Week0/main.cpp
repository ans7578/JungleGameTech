#include <Windows.h>


#pragma comment(lib, "user32")
#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")


#include <d3d11.h>
#include <d3dcompiler.h>

#include "URenderer.h"

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
	//윈도우 클래스 이름
	WCHAR WindowClass[] = L"JungleWindowClass";

	//윈도우 타이틀바에 표시될 이름
	WCHAR Title[] = L"Game Tech Lab";

	//각종 메시지를 처리할 함수인 wndProc의 함수 포인터를
	// windowClass 구조체에 넣는다.
	WNDCLASSW wndclass = { 0, WndProc, 0, 0, 0, 0, 0, 0, 0, WindowClass };

	//윈도우 등록
	RegisterClassW(&wndclass);


	//1024 * 1024 크기에 윈도우 생성

	HWND hwnd = CreateWindowExW(0, WindowClass, Title,
		WS_POPUP | WS_VISIBLE | WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 1024, 1024,
		nullptr, nullptr, hInstance, nullptr);


	URenderer renderer;

	renderer.Create(hwnd);
	renderer.CreateShader();

	//렌더러와 쉐이더 생성 이후 버텍스 버퍼를 생성한다.


	// 삼각형을 하드 코딩(삼각형 정점 3개의 포지션과 색상값을 정의해준다)
	FVertexSimple triangle_vertices[] =
	{
		{  0.0f,  1.0f, 0.0f,  1.0f, 0.0f, 0.0f, 1.0f }, // Top vertex (red)
		{  1.0f, -1.0f, 0.0f,  0.0f, 1.0f, 0.0f, 1.0f }, // Bottom-right vertex (green)
		{ -1.0f, -1.0f, 0.0f,  0.0f, 0.0f, 1.0f, 1.0f }  // Bottom-left vertex (blue)
	};

	FVertexSimple* vertices = triangle_vertices;
	UINT ByteWidth = sizeof(triangle_vertices);
	UINT NumVertices = sizeof(triangle_vertices) / sizeof(FVertexSimple);

	//버텍스 버퍼 생성


	/* D3D11_USAGE
		해당 리소스가 CPU와 GPU 중 어느 쪽에서 주로 사용될지를 나타내는 열거형입니다.

		D3D11_USAGE_DEFAULT: GPU에서 주로 사용되며, CPU에서 직접 접근할 수 없습니다. 일반적인 렌더링에 적합합니다.(GPU에서만 접근 가능)
		D3D11_USAGE_IMMUTABLE: 리소스가 생성된 후 변경되지 않음을 나타냅니다. CPU에서 데이터를 설정한 후에는 변경할 수 없습니다. 주로 정적 데이터에 사용됩니다.(GPU에서만 접근 가능)(가장 빠름)
		D3D11_USAGE_DYNAMIC: CPU에서 자주 변경되는 리소스에 적합합니다. CPU에서 데이터를 업데이트할 수 있으며, GPU에서 읽을 수 있습니다.
		D3D11_USAGE_STAGING: CPU와 GPU 간의 데이터 전송을 위해 사용됩니다. 주로 리소스를 읽거나 쓰기 위해 사용됩니다.(CPU에서만 접근 가능, GPU에선 복사만 가능)
	
	*/


	D3D11_BUFFER_DESC vertexBufferDesc = {};
	vertexBufferDesc.ByteWidth = ByteWidth; // 정점 데이터의 전체 크기
	vertexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER; // 정점 버퍼로 사용됨

	D3D11_SUBRESOURCE_DATA vertexBufferData = { vertices };

	ID3D11Buffer* vertexBuffer = nullptr;
	renderer.Device->CreateBuffer(&vertexBufferDesc, &vertexBufferData, &vertexBuffer);



	bool bIsExit = false;

	//각종 생성하는 코드를 여기에 추가한다.


	//MainLoop(Quit Message가 들어오기 전까지 아래 루프를 무한히 실행한다)
	while (bIsExit == false)
	{
		MSG msg;

		//처리할 메시지가 없을때까지수행
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			// 키 입력 메시지를 번역
			TranslateMessage(&msg);

			//메시지를 적절한 윈도우 프로시저에 전달, 메시지가 위에서 등록한 WndProc로 전달
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT)
			{
				bIsExit = true;
				break;
			}
		}
		////////////////////////////////////
		// 매번 실행되는 코드를 여기에 추가합니다.

		//준비 작업
		renderer.Prepare();
		renderer.PrepareShader();

		//생성한 버텍스버러를 넘겨 실제 렌더링 호출
		renderer.RenderPrimitive(vertexBuffer, NumVertices);


		//다 그렸으면 버퍼 교환
		renderer.SwapBuffer();

		/////////////////////////////////////
	}

	//소멸하는 코드를 여기에 추가합니다.
	vertexBuffer->Release();
	renderer.ReleaseShader();
	renderer.Release();

	return 0;
}

