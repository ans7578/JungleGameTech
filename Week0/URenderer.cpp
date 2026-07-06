#include "URenderer.h"

void URenderer::Create(HWND hWindow)
{
	//Direct3D 장치 및 스왑 체인 생성
	CreateDeviceAndSwapChain(hWindow);
	
	//프레임버퍼생성
	CreateFrameBuffer();


	//래스터라이저 상태 생성
	CreateRasterizerState();
}

void URenderer::CreateDeviceAndSwapChain(HWND hWindow)
{
	//지원하는 다렉 기능 레벨을 정의
	D3D_FEATURE_LEVEL featurelevels[] = { D3D_FEATURE_LEVEL_11_0 };

	//스왑체인 구조체 설정 초기화

	DXGI_SWAP_CHAIN_DESC swapChainDesc = {};

	swapChainDesc.BufferDesc.Width = 0; //자동으로 설정
	swapChainDesc.BufferDesc.Height = 0; //자동으로 설정	
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM; //화면에 출력될 색상 포맷
	swapChainDesc.SampleDesc.Count = 1; //멀티샘플링을 사용하지 않음
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; //렌더타겟으로 사용
	swapChainDesc.BufferCount = 2; //버퍼 개수, 더블 버퍼링을 사용하므로 2개.
	swapChainDesc.OutputWindow = hWindow; //출력할 윈도우 핸들
	swapChainDesc.Windowed = TRUE; //윈도우 모드
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD; //스왑 효과, 최신 권장 방식

	//Direct3D 장치 및 스왑체인 생성

	D3D11CreateDeviceAndSwapChain(
		nullptr, //기본 어댑터 사용
		D3D_DRIVER_TYPE_HARDWARE, //하드웨어 가속 사용
		nullptr, //소프트웨어 드라이버 사용하지 않음
		D3D11_CREATE_DEVICE_BGRA_SUPPORT | D3D11_CREATE_DEVICE_DEBUG, //장치 생성 플래그, BGRA 지원 및 디버그 모드
		featurelevels, //지원할 기능 레벨 배열
		ARRAYSIZE(featurelevels), //기능 레벨 배열 크기
		D3D11_SDK_VERSION, //Direct3D SDK 버전
		&swapChainDesc, //스왑체인 구조체 포인터
		&SwapChain, //생성된 스왑체인 포인터 반환
		&Device, //생성된 장치 포인터 반환
		nullptr, //선택한 기능 레벨 반환하지 않음
		&DeviceContext //생성된 장치 컨텍스트 포인터 반환
	);

	SwapChain->GetDesc(&swapChainDesc); //스왑체인 구조체 정보 가져오기;

	//뷰포트 정보 설정
	/*
	typedef struct D3D11_VIEWPORT
    {
    FLOAT TopLeftX;
    FLOAT TopLeftY;
    FLOAT Width;
    FLOAT Height;
    FLOAT MinDepth;
    FLOAT MaxDepth;
    } 	D3D11_VIEWPORT;
	*/
	ViewportInfo = { 0.f, 0.f, (float)swapChainDesc.BufferDesc.Width, (float)swapChainDesc.BufferDesc.Height, 0.f, 1.f };

}

void URenderer::CreateFrameBuffer()
{
	//스왑 체인으로부터 백 버퍼 텍스처 가져오기
	SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&FrameBuffer);

	//D3D11_RENDER_TARGET_VIEW_DESC 구조체를 사용하여 렌더 타겟 뷰 생성

	D3D11_RENDER_TARGET_VIEW_DESC frameBufferRTVDesc = {};

	frameBufferRTVDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM_SRGB;
	frameBufferRTVDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D; //렌더 타겟 뷰의 차원을 설정함

	Device->CreateRenderTargetView(FrameBuffer, &frameBufferRTVDesc, &FrameBufferRTV); //렌더 타겟 뷰 생성


}

void URenderer::CreateRasterizerState()
{
	D3D11_RASTERIZER_DESC rasterizerDesc = {};
	
	rasterizerDesc.FillMode = D3D11_FILL_SOLID; //채우기 모드, 솔리드로 설정
	rasterizerDesc.CullMode = D3D11_CULL_BACK; //컬링 모드, 뒷면 컬링

	Device->CreateRasterizerState(&rasterizerDesc, &RasterizerState); //래스터라이저 상태 생성

}

void URenderer::SwapBuffer()
{
	SwapChain->Present(1, 0); //스왑체인 프레젠트 호출, 1은 수직동기화, 0은 플래그 없음
}

//다렉 장치 및 스왑 체인을 해제하는 함수
void URenderer::ReleaseDeviceAndSwapChain()
{
	if (DeviceContext)
	{
		DeviceContext->Flush(); //GPU에 남아있는 명령을 모두 실행
	}

	if (SwapChain)
	{
		SwapChain->Release();
		SwapChain = nullptr;
	}

	if (Device)
	{
		Device->Release();
		Device = nullptr;
	}
	if (DeviceContext)
	{
		DeviceContext->Release();
		DeviceContext = nullptr;
	}

}

void URenderer::ReleaseFrameBuffer()
{
	if (FrameBuffer)
	{
		FrameBuffer->Release();
		FrameBuffer = nullptr;
	}
	if (FrameBufferRTV)
	{
		FrameBufferRTV->Release();
		FrameBufferRTV = nullptr;
	}
}

void URenderer::ReleaseRasterizerState()
{
	if (RasterizerState)
	{
		RasterizerState->Release();
		RasterizerState = nullptr;
	}
}
//렌더러에 사용된 모든 리소스를 해제하는 함수
void URenderer::Release()
{
	RasterizerState->Release();

	//렌더 타겟을 초기화
	DeviceContext->OMSetRenderTargets(0, nullptr, nullptr);	

	ReleaseFrameBuffer();
	ReleaseDeviceAndSwapChain();
}
