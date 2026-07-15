#include "URenderer.h"


void URenderer::Create(HWND hWindow)
{
	CreateDeviceSwapChain(hWindow);

	CreateFrameBuffer();

	CreateRasterizerState();

	CreateShader();
}

void URenderer::CreateDeviceSwapChain(HWND hWindow)
{
	D3D_FEATURE_LEVEL featureLevels[] = { D3D_FEATURE_LEVEL_11_0 };


	DXGI_SWAP_CHAIN_DESC swapChainDesc = {};

	swapChainDesc.BufferDesc.Width = 0;
	swapChainDesc.BufferDesc.Height = 0;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	swapChainDesc.SampleDesc.Count = 1;//멀티 샘플링 비활성화
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;//렌더 타겟으로 사용
	swapChainDesc.BufferCount = 2;//더블 버퍼링
	swapChainDesc.OutputWindow = hWindow;//렌더링할 창 핸들
	swapChainDesc.Windowed = TRUE; //창 모드
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD; //스왑 방식

	// Direct3D 장치와 스왑 체인을 생성
	D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr,
		D3D11_CREATE_DEVICE_BGRA_SUPPORT | D3D11_CREATE_DEVICE_DEBUG,
		featureLevels, ARRAYSIZE(featureLevels), D3D11_SDK_VERSION,
		&swapChainDesc, &SwapChain, &Device, nullptr, &DeviceContext);

	// 생성된 스왑 체인의 정보 가져오기(desc에 스왑체인 정보 넣기)
	SwapChain->GetDesc(&swapChainDesc);

	ViewportInfo = { 0.f, 0.f, (float)swapChainDesc.BufferDesc.Width,
		(float)swapChainDesc.BufferDesc.Height, 0.f,1.f };
}

void URenderer::CreateFrameBuffer()
{
	SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&FrameBuffer);


	D3D11_RENDER_TARGET_VIEW_DESC frameBufferRTVDesc = {};
	
	frameBufferRTVDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM_SRGB;
	frameBufferRTVDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D; //2d텍스쳐

	Device->CreateRenderTargetView(FrameBuffer, &frameBufferRTVDesc, &FrameBufferRTV);


}

void URenderer::CreateRasterizerState()
{
	D3D11_RASTERIZER_DESC rasterizerDesc = { };

	rasterizerDesc.FillMode = D3D11_FILL_SOLID;
	rasterizerDesc.CullMode = D3D11_CULL_BACK;


	Device->CreateRasterizerState(&rasterizerDesc, &RasterizerState);

}

void URenderer::CreateShader()
{
	ID3DBlob* vertexShaderBlob;

	ID3DBlob* vertexShaderErrorMSGBlob;


	ID3DBlob* pixelhaderBlob;


	D3DCompileFromFile(L"ShaderW0.hlsl", nullptr, nullptr,
		"mainVS", "vs_5_0", 0, 0, &vertexShaderBlob, &vertexShaderErrorMSGBlob);

	Device->CreateVertexShader(vertexShaderBlob->GetBufferPointer(),
		vertexShaderBlob->GetBufferSize(), nullptr, &SimpleVertexShader);


	D3DCompileFromFile(L"ShaderW0.hlsl", nullptr, nullptr,
		"mainPS", "ps_5_0", 0, 0, &pixelhaderBlob, nullptr);

	Device->CreatePixelShader(pixelhaderBlob->GetBufferPointer(),
		pixelhaderBlob->GetBufferSize(), nullptr, &SimplePixelShader);

	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	Device->CreateInputLayout(layout, ARRAYSIZE(layout), vertexShaderBlob->GetBufferPointer(), vertexShaderBlob->GetBufferSize(), &SimpleInputLayout);

	Stride = 28;
}

void URenderer::Preapre()
{
	DeviceContext->ClearRenderTargetView(FrameBufferRTV, Clear);

	DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	DeviceContext->RSSetViewports(1, &ViewportInfo);
	DeviceContext->RSSetState(RasterizerState);

	DeviceContext->OMSetRenderTargets(1, &FrameBufferRTV, nullptr);
	DeviceContext->OMSetBlendState(nullptr, nullptr, 0xffffffff);

}

void URenderer::PrepareShader()
{
	DeviceContext->VSSetShader(SimpleVertexShader, nullptr, 0);
	DeviceContext->PSSetShader(SimplePixelShader, nullptr, 0);
	DeviceContext->IASetInputLayout(SimpleInputLayout);

}

void URenderer::RenderPrimitive(ID3D11Buffer* pBuffer, UINT numVertices)
{
	UINT offset = 0;
	DeviceContext->IASetVertexBuffers(0, 1, &pBuffer, &Stride, &offset);

	DeviceContext->Draw(numVertices, 0);
}

void URenderer::Release()
{
	ReleaseRasterizerState();

	DeviceContext->OMSetRenderTargets(0, nullptr, nullptr);

	ReleaseFrameBuffer();
	ReleaseDeviceAndSwapChain();
}

void URenderer::ReleaseDeviceAndSwapChain()
{
	
	if (DeviceContext)
	{
		DeviceContext->Flush(); // 남아있는 GPU 명령 실행
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

void URenderer::SwapBuffer()
{
	SwapChain->Present(1, 0);
}
