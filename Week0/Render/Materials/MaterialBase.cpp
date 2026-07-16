#include "MaterialBase.h"
#include "../URenderer.h"


UMaterialBase::UMaterialBase(ID3D11VertexShader* pVS, ID3D11PixelShader* pPS, ID3D11ShaderResourceView* pSRV, ID3D11SamplerState* pSamplerState, ID3D11Buffer* pConstantBuffer)
{
	m_pVertexShader = pVS;
	
	m_pPixelShader = pPS;
	
	m_pShaderResourceViews = pSRV;
	m_pSamplerState = pSamplerState;
	m_pConstantBuffer = pConstantBuffer;



	m_pVertexShader->AddRef();
	m_pPixelShader->AddRef();
	m_pShaderResourceViews->AddRef();
	m_pConstantBuffer->AddRef();
	m_pSamplerState->AddRef();
}


UMaterialBase::~UMaterialBase()
{
	ReleaseMaterial();
}

void UMaterialBase::UpdateMaterialConstantBuffer(URenderer* render, const void* pCBuffer, UINT iBufferDataSize)
{
	render->UpdateConstantBuffer(pCBuffer, iBufferDataSize, URenderer::CBUFFER_WORLD);
}

void UMaterialBase::RenderDebug()
{
}

void UMaterialBase::Bind(URenderer* render)
{

	render->DeviceContext->VSSetShader(m_pVertexShader.Get(), nullptr, 0);
	render->DeviceContext->PSSetShader(m_pPixelShader.Get(), nullptr, 0);
	render->DeviceContext->PSSetShaderResources(0, 1, m_pShaderResourceViews.GetAddressOf());
	render->DeviceContext->PSSetSamplers(0, 1, m_pSamplerState.GetAddressOf());


	render->DeviceContext->VSSetConstantBuffers(URenderer::CBUFFER_MATERIAL, 1, m_pConstantBuffer.GetAddressOf());

}

void UMaterialBase::ReleaseMaterial()
{
	

}
