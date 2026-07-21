#include "MaterialBase.h"
#include "../Render/URenderer.h"



UMaterialBase::UMaterialBase()
{
}

UMaterialBase::~UMaterialBase()
{
	ReleaseMaterial();
}

HRESULT UMaterialBase::Init()
{

	return S_OK;
}

void UMaterialBase::AddTexture(ComPtr<ID3D11ShaderResourceView> pSRV)
{
	m_pShaderResourceViews.push_back(pSRV);
}



void UMaterialBase::UpdateMaterialConstantBuffer(URenderer* renderer, const void* pCBufferData, UINT iBufferDataSize)
{
	renderer->UpdateConstantBuffer(pCBufferData, iBufferDataSize, URenderer::CBUFFER_MATERIAL);
}

void UMaterialBase::RenderDebug()
{
}


void UMaterialBase::ReleaseMaterial()
{
	

}
