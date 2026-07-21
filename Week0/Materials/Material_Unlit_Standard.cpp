#include "Material_Unlit_Standard.h"
#include "../Render/URenderer.h"
#include "../Managers/ResourceManager.h"


UMaterial_Unlit_Standard::UMaterial_Unlit_Standard()
{
	m_pShaderProgram = CResourceManager::GetInstance().LoadShaderProgram(L"Unlit_Standard");

	AddTexture(CResourceManager::GetInstance().LoadTexture(L"Doro"));
	AddTexture(CResourceManager::GetInstance().LoadTexture(L"Phoebe"));
}

UMaterial_Unlit_Standard::~UMaterial_Unlit_Standard()
{
}

HRESULT UMaterial_Unlit_Standard::Init()
{
	m_fBufferData.Diffuse = FColor(1.f, 1.f, 1.f, 1.f);

	return S_OK;
}

void UMaterial_Unlit_Standard::Bind(URenderer* render)
{
	render->DeviceContext->VSSetShader(m_pShaderProgram.lock()->pVertexShader.Get(), nullptr, 0);
	render->DeviceContext->PSSetShader(m_pShaderProgram.lock()->pPixelShader.Get(), nullptr, 0);
	render->DeviceContext->IASetInputLayout(m_pShaderProgram.lock()->pInputLayout.Get());

	m_fBufferData.Diffuse = FColor(1.f, 0.f, 0.f, 1.f);

	render->UpdateConstantBuffer(&m_fBufferData, sizeof(m_fBufferData), URenderer::CBUFFER_MATERIAL);

	render->SetConstantBuffer(URenderer::CBUFFER_MATERIAL);


	if (m_pShaderResourceViews[0].Get() != nullptr)
	{
		render->DeviceContext->PSSetShaderResources(0, 1, m_pShaderResourceViews[0].GetAddressOf());
		render->SetSamplerState(0, URenderer::ESamplerStateType::SAMPLERSTATE_LINEAR_WRAP);
	}
}

const wchar_t* UMaterial_Unlit_Standard::GetMaterialName()
{
    return L"Material_Diffuse";
}
