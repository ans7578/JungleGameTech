#include "MaterialBase.h"
#include "../URenderer.h"



UMaterialBase::~UMaterialBase()
{
	ReleaseMaterial();
}

void UMaterialBase::SetUpMaterial(weak_ptr<FShaderProgram> pShaderProgram, ID3D11ShaderResourceView* pSRV)
{
	m_pShaderProgram = pShaderProgram;

	m_pShaderResourceViews = pSRV;


	int a = 5;
}


void UMaterialBase::UpdateMaterialConstantBuffer(URenderer* render, const void* pCBufferData, UINT iBufferDataSize)
{
	render->UpdateConstantBuffer(pCBufferData, iBufferDataSize, URenderer::CBUFFER_WORLD);
}

void UMaterialBase::RenderDebug()
{
}

void UMaterialBase::Bind(URenderer* render)
{

	render->DeviceContext->VSSetShader(m_pShaderProgram.lock()->pVertexShader.Get() , nullptr, 0);
	render->DeviceContext->PSSetShader(m_pShaderProgram.lock()->pPixelShader.Get(), nullptr, 0);
	render->DeviceContext->IASetInputLayout(m_pShaderProgram.lock()->pInputLayout.Get());

	m_fBufferData.Diffuse = FColor(1.f, 0.f, 0.f, 1.f);

	render->UpdateConstantBuffer(&m_fBufferData, sizeof(m_fBufferData), URenderer::CBUFFER_MATERIAL);

	render->SetConstantBuffer(URenderer::CBUFFER_MATERIAL);

	
	if (m_pShaderResourceViews.Get() != nullptr)
	{
		render->DeviceContext->PSSetShaderResources(0, 1, m_pShaderResourceViews.GetAddressOf());
		render->SetSamplerState(0, URenderer::ESamplerStateType::SAMPLERSTATE_LINEAR_WRAP);
	}
}

void UMaterialBase::ReleaseMaterial()
{
	

}
