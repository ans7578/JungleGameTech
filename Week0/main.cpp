#include <Windows.h>


#pragma comment(lib, "user32")
#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")


#include <d3d11.h>
#include <d3dcompiler.h>

#include "URenderer.h"
#include "Cube.h"
#include "Sphere.h"

enum ETypePrimitive
{
	EPT_Triangle,
	EPT_Cube,
	EPT_Sphere,
	EPT_Max,
};


extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);


int WINAPI WndProc(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	return 0;
}


//각종 메시지를 처리할 함수
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hwnd, message, wParam, lParam))
	{
		return true;
	}


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


	//ImGui 생성
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplWin32_Init((void*)hwnd);
	ImGui_ImplDX11_Init(renderer.Device, renderer.DeviceContext);



	//렌더러와 쉐이더 생성 이후 버텍스 버퍼를 생성한다.


	// 삼각형을 하드 코딩(삼각형 정점 3개의 포지션과 색상값을 정의해준다)
	FVertexSimple triangle_vertices[] =
	{
		{  0.0f,  1.0f, 0.0f,  1.0f, 0.0f, 0.0f, 1.0f }, // Top vertex (red)
		{  1.0f, -1.0f, 0.0f,  0.0f, 1.0f, 0.0f, 1.0f }, // Bottom-right vertex (green)
		{ -1.0f, -1.0f, 0.0f,  0.0f, 0.0f, 1.0f, 1.0f }  // Bottom-left vertex (blue)
	};

	UINT numVerticesTriangle = sizeof(triangle_vertices) / sizeof(FVertexSimple);
	UINT numVerticesCube= sizeof(cube_vertices) / sizeof(FVertexSimple);
	UINT numVerticesSphere= sizeof(sphere_vertices) / sizeof(FVertexSimple);

	float scaleMod = 0.1f;
	for (UINT i = 0; i < numVerticesSphere; ++i)
	{
		sphere_vertices[i].x *= scaleMod;
		sphere_vertices[i].y *= scaleMod;
		sphere_vertices[i].z *= scaleMod;
	}

	ID3D11Buffer* vertexBufferTriangle = renderer.CreateVertexBuffer(triangle_vertices, sizeof(triangle_vertices));
	ID3D11Buffer* vertexBufferCube= renderer.CreateVertexBuffer(cube_vertices, sizeof(cube_vertices));
	ID3D11Buffer* vertexBufferSphere= renderer.CreateVertexBuffer(sphere_vertices, sizeof(sphere_vertices));

	ETypePrimitive typePrimitive = EPT_Triangle;
	
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
	

		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
		
		/////////////////////////////////////////////////////
		//이후 ImGui  UI 컨트롤 추가는  ImGui::NewFrame()과  ImGui::Render()사이인 여기에 추가합니다.
	
		ImGui::Begin("Jungle Property Window");

		ImGui::Text("Hello Jungle World!");

		//if (ImGui::Button("Quit this app"))
		//{
		//	PostMessage(hwnd, WM_QUIT, 0, 0);
		//}

		if (ImGui::Button("ChangePrimitive"))
		{
			switch (typePrimitive)
			{
			case EPT_Triangle:
				typePrimitive = EPT_Cube;
				break;
			case EPT_Cube:
				typePrimitive = EPT_Sphere;
				break;
			case EPT_Sphere:
				typePrimitive = EPT_Triangle;
				break;
			default:
				break;
			}
		}



		ImGui::End();

		////////////////////////////////////////////////////
		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());


		switch (typePrimitive)
		{
		case EPT_Triangle:
			renderer.RenderPrimitive(vertexBufferTriangle, numVerticesTriangle);
			break;
		case EPT_Cube:
			renderer.RenderPrimitive(vertexBufferCube, numVerticesCube);
			break;
		case EPT_Sphere:
			renderer.RenderPrimitive(vertexBufferSphere, numVerticesSphere);
			break;
		default:
			break;
		}


		//다 그렸으면 버퍼 교환
		renderer.SwapBuffer();
		/////////////////////////////////////
	}
	//소멸하는 코드를 여기에 추가합니다.

	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	renderer.ReleaseVertexBuffer(vertexBufferTriangle);
	renderer.ReleaseVertexBuffer(vertexBufferCube);
	renderer.ReleaseVertexBuffer(vertexBufferSphere);


	renderer.ReleaseShader();
	renderer.Release();

	return 0;
}

