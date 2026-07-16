#include "Headers.h"

#include "./Actors/Actor.h"
#include "./Meshs/Mesh.h"
#include "Render/URenderer.h"

//Managers
#include "./Managers/LevelManager.h"
#include "./Managers/ResourceManager.h"
#include "./Managers/InputManager.h"

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
	#if defined(_DEBUG)
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	#endif

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
	renderer.CreateConstantBuffer();

	//매니저 세팅
	CResourceManager::GetInstance().SetupResource(&renderer);
	CLevelManager::GetInstance().SetupLevels();
	CInputManager::GetInstance().SetupInput();

	//ImGui 생성
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplWin32_Init((void*)hwnd);
	ImGui_ImplDX11_Init(renderer.Device.Get(), renderer.DeviceContext.Get());


	bool bIsExit = false;
	//각종 생성하는 코드를 여기에 추가한다.



	bool bBoundsBallToScreen = true;
	bool bPinballMovement = true;

	

	const int targetFPS = 60;
	const double targetFrameTime = 1000.0f / targetFPS;

	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);

	LARGE_INTEGER startTime, endTime;
	double elapsedTime = 0.0f;

	
	CLevelManager::GetInstance().Init_Level();
	
	//키입력을 처리받는 루프
	//MainLoop(Quit Message가 들어오기 전까지 아래 루프를 무한히 실행한다)
	while (bIsExit == false)
	{
		QueryPerformanceCounter(&startTime);
		MSG msg;

		CInputManager::GetInstance().Update();

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
			CInputManager::GetInstance().UpdateInput(msg);
			if (msg.message == WM_LBUTTONDOWN)
			{

				int mouseX = LOWORD(msg.lParam);
				int mouseY = HIWORD(msg.lParam);
			}
		}
		/*
		
		*/
		////////////////////////////////////
		// 매번 실행되는 코드를 여기에 추가합니다.
	
		CLevelManager::GetInstance().Update_Level();
		CLevelManager::GetInstance().LateUpdate_Level();

		//렌더 준비 작업
		renderer.Prepare();
		renderer.PrepareShader();
		
		//생성한 버텍스버러를 넘겨 실제 렌더링 호출
		
		CLevelManager::GetInstance().Render_Level(&renderer);

#pragma region ImGuiRender
		#if defined(_DEBUG)

			ImGui_ImplDX11_NewFrame();
			ImGui_ImplWin32_NewFrame();
			ImGui::NewFrame();

			
			CLevelManager::GetInstance().Render_Debug();


			ImGui::Render();
			ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
		#endif
#pragma endregion

		

		//다 그렸으면 버퍼 교환
		renderer.SwapBuffer();

		do
		{
			Sleep(0);
			//루프 종료시간 기록
			QueryPerformanceCounter(&endTime);

			//한프레임이 소요된 시간 계산
			elapsedTime = (endTime.QuadPart - startTime.QuadPart) * 1000.0 / frequency.QuadPart;
		} while (elapsedTime < targetFrameTime);
		/////////////////////////////////////
	}
	//소멸하는 코드를 여기에 추가합니다.

	

	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	

	//매니저 해제
	CResourceManager::GetInstance().ReleaseSingleton();
	CLevelManager::GetInstance().ReleaseSingleton();
	CInputManager::GetInstance().ReleaseSingleton();


	renderer.ReleaseConstantBuffer();
	renderer.ReleaseShader();

	renderer.Release();

	
	return 0;
}

