#pragma once

#include "../Headers.h"
#include "../Structs.h"


class URenderer
{
public:
	enum ECBufferType
	{
		CBUFFER_CAMERA = 0,
		CBUFFER_WORLD = 1,
		CBUFFER_MATERIAL = 2,

		CBUFFER_END
	};

	enum ESamplerStateType
	{
		SAMPLERSTATE_LINEAR_WRAP = 0,	
		SAMPLERSTATE_END
	};


	struct FWorldBufferData
	{
		XMMATRIX World;
	};


	struct FCameraBufferData
	{
		XMMATRIX View;
		XMMATRIX Projection;
	};

	


public:
	//Direct3D 11장치와 장치 컨텍스트 및 스왑 체인을 관리하기 위한 포인트
	ComPtr<ID3D11Device> Device = nullptr; // GPU와 통신하기 위한 Direct3D장치
	ComPtr <ID3D11DeviceContext> DeviceContext = nullptr; // GPU명령 실행을 담당하는 컨텍스트
	ComPtr <IDXGISwapChain> SwapChain = nullptr; // 프레임 버퍼를 교체하는데 사용되는 스왑체인

	//렌더링에 필요한 리소스 및 상태를 관리하기 위한 변수들

	ComPtr <ID3D11Texture2D> FrameBuffer = nullptr; // 화면출력용텍스처
	ComPtr<ID3D11RenderTargetView> FrameBufferRTV = nullptr; // 텍스처를 렌더타겟으로 사용하는 뷰
	ComPtr<ID3D11RasterizerState> RasterizerState = nullptr; //래스터라이저 상태(컬링, 채우기 모드 등 정의)


	FLOAT ClearColor[4] = { 0.025f, 0.025f, 0.025f, 1.0f }; // 화면을 초기화(clear)할 때 사용할 색상 (RGBA)
	D3D11_VIEWPORT ViewportInfo;  //렌더링 영역을 정의하는 뷰포트 정보

	//unsigned int Stride; // 정점 데이터의 한 정점당 바이트 수 (3개의 float로 구성된 정점)

public:
	//렌더러 초기화 함수
	void Create(HWND hWindow);

	void CreateDeviceAndSwapChain(HWND hWindow);

	void CreateFrameBuffer();

	void CreateRasterizerState();

	void CreateShader(const wchar_t* szFilePath, ID3D11VertexShader** ppOutVertexShader, ID3D11PixelShader** ppOutPixelShader, D3D11_INPUT_ELEMENT_DESC* Layout, UINT layoutSize);

	void CreateShader(const wchar_t* szFilePath, ID3D11VertexShader** ppOutVertexShader, ID3D11PixelShader** ppOutPixelShader, ID3D11InputLayout** ppOutInputLayout);

	void CreateVertexBuffer(void* pVertexData, UINT byteWidth, D3D11_USAGE usage, ID3D11Buffer** ppOutVertexBuffer);

	void CreateIndexBuffer(UINT* indices, UINT byteWidth, D3D11_USAGE usage, ID3D11Buffer** ppOutIndexBuffer);


	void CreateConstantBuffer();

	void CreateShaderResources(const wchar_t* szFilePath, ID3D11ShaderResourceView** ppOutSRV);


	void CreateSamplerState();


	void SwapBuffer();

	void Prepare();
	
	void PrepareShader();

	//주의! 카메라는 액터보다 항상 먼저 업데이트 되어야한다.(카메라의 영향을 받는 객체들보다 늦게 갱신되면X)
	void UpdateConstantBuffer(const void* pCBuffer, UINT iBufferDataSize, ECBufferType eCBufferType);



	void SetSamplerState(UINT iSamplerSlot,  ESamplerStateType eSamplerType);

	void SetConstantBuffer(ECBufferType eBufferType);

	void RenderPrimitive(ID3D11Buffer* pBuffer, UINT iVertexStride, UINT NumVertices);

	void RenderPrimitiveIndexed(UINT NumIndices);


	void ReleaseDeviceAndSwapChain();
	void ReleaseFrameBuffer();
	void ReleaseRasterizerState();
	void ReleaseShader();

	void ReleaseVertexBuffer(ID3D11Buffer* vertexBuffer);

	void ReleaseIndexBuffer(ID3D11Buffer* indexBuffer);


	void ReleaseConstantBuffer();

	void Release();
		

private:
	void		CreateInputLayout(ID3DBlob* pVertexBlob, ID3D11InputLayout** ppOutInputLayout);

private:
	ComPtr<ID3D11Buffer> ConstantBuffers[CBUFFER_END];// 쉐이더에 데이터를 전달하기 위한 상수 버퍼

	ComPtr<ID3D11SamplerState> m_samplerStates[SAMPLERSTATE_END];

};