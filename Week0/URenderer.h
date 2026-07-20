#pragma once


// D3D 사용에 필요한 라이브러리들을 링크합니다.
#pragma comment(lib, "user32")
#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")

// D3D 사용에 필요한 헤더파일들을 포함합니다.
#include <d3d11.h>
#include <d3dcompiler.h>

#pragma region Structs
struct FVector
{
	float x, y, z;
	
	FVector(float scalar = 0.f) : x(scalar), y(scalar), z(scalar){}

	FVector(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

	void operator+(FVector& fVector)
	{
		x += fVector.x;
		y += fVector.y;
		z += fVector.z;

	}

	FVector& operator+=(FVector& fVector)
	{
		*this + fVector;

		return *this;
	}
};

// 1. Define the triangle vertices
struct FVertexSimple
{
	float x, y, z;    // Position
	float r, g, b, a; // Color

	void SetColor(float _r, float _g, float _b, float _a)
	{
		r = _r;
		g = _g;
		b = _b;
		a = _a;
	}
	void SetColor(FVector color)
	{
		this->SetColor(color.x, color.y, color.z, 1.f);
	}
};

#pragma endregion


class URenderer
{
public:
	struct FConstantBuffer
	{
		FVector Offset;
		float	Pad;
		FVector Scale;
		float	Pad2;
		FVector Color;
		float	Pad3;
	};

public:

	//Direct3D 11장치와 장치 컨텍스트 및 스왑 체인을 관리하기 위한 포인트
	ID3D11Device* Device = nullptr; // GPU와 통신하기 위한 Direct3D장치
	ID3D11DeviceContext* DeviceContext = nullptr; // GPU명령 실행을 담당하는 컨텍스트
	IDXGISwapChain * SwapChain = nullptr; // 프레임 버퍼를 교체하는데 사용되는 스왑체인

	//렌더링에 필요한 리소스 및 상태를 관리하기 위한 변수들

	ID3D11Texture2D* FrameBuffer = nullptr; // 화면출력용텍스처
	ID3D11RenderTargetView* FrameBufferRTV = nullptr; // 텍스처를 렌더타겟으로 사용하는 뷰
	ID3D11RasterizerState* RasterizerState = nullptr; //래스터라이저 상태(컬링, 채우기 모드 등 정의)
	ID3D11Buffer* ConstantBuffer = nullptr; // 쉐이더에 데이터를 전달하기 위한 상수 버퍼

	
	FLOAT ClearColor[4] = { 0.025f, 0.025f, 0.025f, 1.0f }; // 화면을 초기화(clear)할 때 사용할 색상 (RGBA)
	D3D11_VIEWPORT ViewportInfo;  //렌더링 영역을 정의하는 뷰포트 정보


	ID3D11VertexShader* SimpleVertexShader = nullptr; // 정점 쉐이더
	ID3D11PixelShader* SimplePixelShader = nullptr; // 픽셀 쉐이더
	ID3D11InputLayout* SimpleInputLayout = nullptr; // 정점 데이터의 형식을 정의하는 입력 레이아웃



	unsigned int Stride; // 정점 데이터의 한 정점당 바이트 수 (3개의 float로 구성된 정점)

public:
	//렌더러 초기화 함수
	void Create(HWND hWindow);

	void CreateDeviceAndSwapChain(HWND hWindow);

	void CreateFrameBuffer();

	void CreateRasterizerState();

	void CreateShader();

	ID3D11Buffer*	CreateVertexBuffer(FVertexSimple* vertices, UINT byteWidth);

	ID3D11Buffer* CreateIndexBuffer(UINT* indices, UINT byteWidth);


	void CreateConstantBuffer();


	void SwapBuffer();

	void Prepare();
	
	void PrepareShader();

	void UpdateConstantBuffer(const FConstantBuffer& cbData);

	void RenderPrimitive(ID3D11Buffer* pBuffer, UINT NumVertices);



	void ReleaseDeviceAndSwapChain();
	void ReleaseFrameBuffer();
	void ReleaseRasterizerState();
	void ReleaseShader();

	void ReleaseVertexBuffer(ID3D11Buffer* vertexBuffer);

	void ReleaseIndexBuffer(ID3D11Buffer* indexBuffer);


	void ReleaseConstantBuffer();

	void Release();



};

