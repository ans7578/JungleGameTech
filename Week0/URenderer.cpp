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

	//스왑체인 구조체 초기화



}

void URenderer::CreateFrameBuffer()
{
}

void URenderer::CreateRasterizerState()
{
}
