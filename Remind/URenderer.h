#pragma once

#pragma comment(lib, "user32")
#pragma	comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")


#include <d3d11.h>
#include <d3dcompiler.h>



class URenderer
{

public:
	//렌더러 초기화 함수
	void	Create(HWND hWindow);

	void	CreateDeviceSwapChain(HWND hWindow);
	void	CreateFrameBuffer();
	void	CreateRasterizerState();
	void	CreateShader();

	void	Preapre();
	void	PrepareShader();

	void	RenderPrimitive(ID3D11Buffer* pBuffer, UINT numVertices);

	void	Release();


	void	ReleaseDeviceAndSwapChain();
	void	ReleaseFrameBuffer();
	void	ReleaseRasterizerState();


	void SwapBuffer();


public:
	ID3D11Device* Device = nullptr;
	ID3D11DeviceContext* DeviceContext = nullptr;
	IDXGISwapChain* SwapChain = nullptr;



	ID3D11Texture2D* FrameBuffer = nullptr;
	ID3D11RenderTargetView* FrameBufferRTV = nullptr;
	ID3D11RasterizerState* RasterizerState = nullptr;
	ID3D11Buffer* ConstantBuffer = nullptr;

	FLOAT			Clear[4] = { 0.025f,0.025f ,0.025f ,1.f };
	D3D11_VIEWPORT	ViewportInfo;
	

	ID3D11VertexShader* SimpleVertexShader;
	ID3D11PixelShader* SimplePixelShader;
	ID3D11InputLayout* SimpleInputLayout;
	unsigned int Stride;


};

