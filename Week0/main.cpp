#include <windows.h>

#include "Sphere.h"
#include "Cube.h"
#include "URenderer.h"

// 여기에 아래 코드를 추가 합니다.

// D3D 사용에 필요한 라이브러리들을 링크합니다.
#pragma comment(lib, "user32")
#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")

// D3D 사용에 필요한 헤더파일들을 포함합니다.
#include <d3d11.h>
#include <d3dcompiler.h>

//ImGui
#include "ImGui/imgui.h"
#include "ImGui/imgui_internal.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>


#pragma region Classes
class UPrimitive
{
public:
	UPrimitive()
	{

	}
	virtual ~UPrimitive()
	{

	}

	virtual void Move()
	{

	}
public:
	FVertexSimple* Vertices = nullptr;
	UINT		NumVertices = 0;
};

//해상도가 1024,1024 기준이기때문에 단일 매개변수로 받음
FVector ToNDC(const FVector screenPT, float ScreenSize)
{
	FVector toNDC;

	toNDC.x = (screenPT.x / ScreenSize) * 2.f - 1.f;
	toNDC.y = 1.f - (screenPT.y / ScreenSize) * 2.f; //윈도우 좌표계는 위로갈수록 작아지니 반대로

	return toNDC;
}


class UBall : public UPrimitive
{

public:
	UBall(FVertexSimple* _vertices)
	{
		TotalNumBalls++;

		Vertices = _vertices;

		NumVertices = sizeof(sphere_vertices) / sizeof(FVertexSimple);

		Location = FVector(0.f, 0.f, 0.f);
		Velocity = FVector(0.f, 0.f, 0.f);

		//적당히 안쪽에서 랜덤하게 위치를 잡는다.
		Location.x = ((float)(rand() % 1000));
		Location.y = ((float)(rand() % 1000));

		Location = ToNDC(Location, 1024.f);

		Velocity.x = ((float)(rand() % 100 - 50) * 0.001f);
		Velocity.y = ((float)(rand() % 100 - 50) * 0.001f);

		Radius = ((float)(rand() % 200 + 20) * 0.001f);

		Color = FVector(1.f, 1.f, 1.f);
		Mass = Radius;



	}
	~UBall()
	{
		TotalNumBalls--;
	}

public:
	void Reset()
	{

	}
	virtual void	Move() override
	{




		Location += Velocity;



	}
	virtual void	Collision()
	{
		boundCount++;
		Color.x = (float)(rand() % 255) * 0.01f;
		Color.y = (float)(rand() % 255) * 0.01f;
		Color.z = (float)(rand() % 255) * 0.01f;
	}
protected:

public:
	// 클래스 이름과, 아래 다섯개의 변수 이름은 변경하지 않습니다.

	FVector Location;
	FVector Velocity;
	FVector Color;
	float Radius;
	float Mass;
	static int TotalNumBalls;
	int	boundCount = 0;
};

#pragma endregion

int UBall::TotalNumBalls = 0;


void CollisionCalc(UBall& ballA, UBall& ballB)
{
	float dx = ballB.Location.x - ballA.Location.x;
	float dy = ballB.Location.y - ballA.Location.y;

	//두 원의 중심 사이의 거리
	float distSq = dx * dx + dy * dy;
	float radiusSum = ballA.Radius + ballB.Radius;

	//둘 정점사이의 거리가 반지름의 합보다 작다 -> 충돌
	if (distSq < radiusSum * radiusSum && distSq > 0.0f)
	{
		ballA.Collision();
		ballB.Collision();

		float distance = sqrtf(distSq);

		//두 원이 겹치는 정도를 계산
		float overlap = 0.5f * (radiusSum - distance);

		/*
			나에게 상대를 빼면, 나를 향하는 벡터가 나온다. 이걸 distance로 나눠 단위벡터를 생성.
		*/
		float normalX = dx / distance;
		float normalY = dy / distance;

		ballA.Location.x -= normalX * overlap;
		ballA.Location.y -= normalY * overlap;
		
		ballB.Location.x += normalX * overlap;
		ballB.Location.y += normalY * overlap;
		
		float dvx = ballA.Velocity.x - ballB.Velocity.x;
		float dvy = ballA.Velocity.y - ballB.Velocity.y;

		//상대가 나를 향하는 속도의 노말 벡터를 내적한다

		float velocityDotNorm = dvx * normalX + dvy * normalY;

		if (velocityDotNorm < 0)//서로 멀어지는 중이면 충돌 계산을 하지 않는다.
		{
			return;
		}
		//질량에 대한 충격량을 계산
		//100짜리와 1짜리가 충돌하면 100짜린 거의 멈춰있되, 1짜린 튕겨나가야함.
		float impulse = (2 * velocityDotNorm) / (ballA.Mass + ballB.Mass);

		ballA.Velocity.x -= impulse * ballB.Mass * normalX;
		ballA.Velocity.y -= impulse * ballB.Mass * normalY;

		ballB.Velocity.x += impulse * ballA.Mass * normalX;
		ballB.Velocity.y += impulse * ballA.Mass * normalY;
	}
}






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
	renderer.CreateConstantBuffer();

	//ImGui 생성
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplWin32_Init((void*)hwnd);
	ImGui_ImplDX11_Init(renderer.Device, renderer.DeviceContext);

	float scaleMod = 0.1f;



	bool bGravity = false;

	bool bIsExit = false;
	//각종 생성하는 코드를 여기에 추가한다.


	const float leftBorder = -1.0f;
	const float rightBorder = 1.0f;
	const float topBorder = 1.0f;
	const float bottomBorder = -1.0f;
	const float sphereRadius = 1.0f;


	bool bBoundsBallToScreen = true;
	bool bPinballMovement = true;


	int targetFPS = 30;
	double targetFrameTime = 1000.0f / targetFPS;

	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);

	LARGE_INTEGER startTime, endTime, prevTime;
	double elapsedTime = 0.0f;


	int maxBalls = 10000;

	int ballCount = 0;


	UPrimitive** Balls = new UPrimitive * [maxBalls];


	ID3D11Buffer* vertexBuffer = nullptr;

	vertexBuffer = renderer.CreateVertexBuffer(sphere_vertices, sizeof(sphere_vertices));
	UINT numVerticesSphere = sizeof(sphere_vertices) / sizeof(FVertexSimple);


	//키입력을 처리받는 루프
	//MainLoop(Quit Message가 들어오기 전까지 아래 루프를 무한히 실행한다)

	QueryPerformanceCounter(&prevTime);

	float gravity = -0.4f;

	//충돌시 색상변경 제어변수
	bool bCollisionChangeColor = false;


	//충돌시 쪼개지기 제어변수
	bool bClickDiviedSphere = false;

	int divideCount = 2;

	while (bIsExit == false)
	{
		QueryPerformanceCounter(&startTime);

		//현재 프레임과 이전 프레임간의 차이
		float deltaTime = (float)(startTime.QuadPart - prevTime.QuadPart) / frequency.QuadPart;
		prevTime = startTime;

		if (deltaTime > 0.1f) deltaTime = 0.1f;

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

		for (int i = 0; i < UBall::TotalNumBalls; i++)
		{
			UBall* ball = (UBall*)Balls[i];

			Balls[i]->Move();

			float renderRadius = ball->Radius;

			FVector veclotiy = ball->Velocity;
			
			if (ball->Location.x < leftBorder + renderRadius)
			{
				ball->Location.x = 2.f * (leftBorder + renderRadius) - ball->Location.x;
				ball->Velocity.x = veclotiy.x * -1.f;

				ball->Collision();

			}
			if (ball->Location.x > rightBorder - renderRadius)
			{
				ball->Location.x = 2.f * (rightBorder - renderRadius) - ball->Location.x;
				ball->Velocity.x = veclotiy.x * -1.f;

				ball->Collision();

			}
			if (ball->Location.y > topBorder - renderRadius)
			{
				ball->Location.y = 2.f * (topBorder - renderRadius) - ball->Location.y;
				ball->Velocity.y = veclotiy.y * -1.f;
				
				ball->Collision();

			}
			if (ball->Location.y < bottomBorder + renderRadius)
			{
				ball->Location.y = 2.f * (bottomBorder + renderRadius) - ball->Location.y;

				ball->Velocity.y = veclotiy.y * -1.f;

				ball->Collision();

			}
		}

		for (int i = 0; i < UBall::TotalNumBalls; i++)
		{
			UBall* ballA = (UBall*)Balls[i];
			for (int j = i + 1; j < UBall::TotalNumBalls; j++)
			{
				UBall* ballB = (UBall*)Balls[j];

				CollisionCalc(*ballA, *ballB);

			}
		}

		if (bGravity)
		{
			for (int i = 0; i < UBall::TotalNumBalls; i++)
			{
				UBall* ball = (UBall*)Balls[i];
				ball->Velocity.y += gravity * deltaTime;
			}
		}

		if (ImGui::IsMouseClicked(ImGuiMouseButton_Left) && bClickDiviedSphere)
		{
			ImGuiIO& io = ImGui::GetIO();

			if (!io.WantCaptureMouse)
			{
				//마우스 좌표를 NDC좌표로 변환

				FVector mouseNDC = ToNDC(FVector(io.MousePos.x, io.MousePos.y, 0.f), 1024.f);

				bool	bClicked = false;
				int		clickedIndex = -1;
				for (int i = 0; i < UBall::TotalNumBalls; i++)
				{
					UBall* ball = (UBall*)Balls[i];

					float dx = mouseNDC.x - ball->Location.x;
					float dy = mouseNDC.y - ball->Location.y;

					float distSq = dx * dx + dy * dy;

					float radiusSq = ball->Radius * ball->Radius;

					//마우스와 공 사이의 거리가 반지름보다 짧다면 클릭된걸로 간주한다.
					if (distSq <= radiusSq)
					{
						bClicked = true;
						clickedIndex = i;

						//공 쪼개기 수식 들어감.
						float childRadius = ball->Radius / divideCount;
						float childMass = ball->Mass / divideCount;
						for (int j = 0; j < divideCount; j++)
						{
							if (UBall::TotalNumBalls >= maxBalls)
							{
								break;
							}

							UBall* newBall = new UBall(sphere_vertices);

							newBall->Radius = childRadius;
							newBall->Mass = childMass;
							newBall->Velocity = ball->Velocity;
							newBall->Location = ball->Location;

							//쪼개진 자식들이 원형으로 퍼져나가게끔 값을 나눈다
							float angle = (2.f * 3.141592f / (float)divideCount) * j;

							FVector direction(cosf(angle) * 0.05f, sinf(angle) * 0.05f, 0.f);

							newBall->Velocity += direction;
							newBall->Location += newBall->Velocity;

							Balls[UBall::TotalNumBalls - 1] = newBall;
						}
					}
					if (bClicked)
					{
						int lastIndex = UBall::TotalNumBalls - 1;

						UPrimitive* temp = Balls[clickedIndex];
						Balls[clickedIndex] = Balls[lastIndex];

						Balls[lastIndex] = temp;

						delete Balls[lastIndex];

						Balls[lastIndex] = nullptr;

						ballCount += (divideCount - 1);
						break;
					}
				}
			}
		}
		renderer.Prepare();
		renderer.PrepareShader();



		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();


		ImGui::Begin("Jungle Property Window");
		{
			ImGui::Text("Hello Jungle World!");

			if (ImGui::Checkbox("Gravity", &bGravity))
			{
				
			}

			if (ImGui::Checkbox("Bounce Change Color", &bCollisionChangeColor))
			{

			}

			if (ImGui::InputInt("Number of Balls", &ballCount))
			{
				if (ballCount > maxBalls)
				{
					ballCount = maxBalls;
				}

				if (ballCount < 0)
				{
					ballCount = 0;
				}
				else if (ballCount > UBall::TotalNumBalls)
				{
					int numNewBalls = ballCount - UBall::TotalNumBalls;
					for (int i = 0; i < numNewBalls; i++)
					{
						if (UBall::TotalNumBalls < maxBalls)
						{
							UBall* ball = new UBall(sphere_vertices);

							Balls[UBall::TotalNumBalls - 1] = ball;
						}
					}
				}
				else if (ballCount < UBall::TotalNumBalls)
				{
					/*
						이중포문을 쓰는건 너무 비효율적이니
						끝자리에 있는 공을 방금 지운 위치에 넣음
					*/
					int numNewBalls = UBall::TotalNumBalls - ballCount;
					for (int i = 0; i < numNewBalls; i++)
					{
						int lastIndex = UBall::TotalNumBalls - 1;
						int randomIndex = rand() % UBall::TotalNumBalls;

						//끝이면 그냥 지우고, 끝이 아니면 끝에 있는 공을 지운 위치로 옮기고 지움
						if (randomIndex != lastIndex)
						{
							UPrimitive* temp = Balls[randomIndex];
							Balls[randomIndex] = Balls[lastIndex];

							Balls[lastIndex] = temp;
						
							delete Balls[lastIndex];
						}
						else
						{
							delete Balls[randomIndex];
						}
						Balls[lastIndex] = nullptr;
					}
				}
			}

			if (ImGui::InputInt("FPS", &targetFPS))
			{
				targetFrameTime = 1000.0f / targetFPS;
			}
		
			if (ImGui::Checkbox("CollsionDivideSphere", &bClickDiviedSphere))
			{

			}
			
			if (ImGui::InputInt("DivideCount", &divideCount))
			{
				if (divideCount < 2)
				{
					divideCount = 2;
				}
			}
		}
		ImGui::End();

		////////////////////////////////////////////////////
		
		URenderer::FConstantBuffer cbData;

		for (int i = 0; i < UBall::TotalNumBalls; i++)
		{
			if (i == 6)
				int a = 5;

			UBall* ball = (UBall*)Balls[i];

			cbData.Offset = ball->Location;
			cbData.Scale = ball->Radius;

			if (bCollisionChangeColor)
			{
				cbData.Color = ball->Color;
			}
			else
			{
				cbData.Color = FVector(1.f, 1.f, 1.f);
			}

			renderer.UpdateConstantBuffer(cbData);
			renderer.RenderPrimitive(vertexBuffer, numVerticesSphere);
		}
		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

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

	vertexBuffer->Release();

	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	
	renderer.ReleaseConstantBuffer();
	renderer.ReleaseShader();
	renderer.Release();


	int size = UBall::TotalNumBalls;

	for (int i = 0; i < size; i++)
	{
		if (Balls[i] != nullptr)
		{
			delete Balls[i];
			Balls[i] = nullptr;
		}
	}
	delete[] Balls;
	Balls = nullptr;

	return 0;
}

