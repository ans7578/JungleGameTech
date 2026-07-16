#pragma once
#include "../../Headers.h"

class URenderer;

class UMaterialBase
{
public:
	UMaterialBase(ID3D11VertexShader* pVS, ID3D11PixelShader* pPS, ID3D11ShaderResourceView* pSRV,
		ID3D11SamplerState* pSamplerState, ID3D11Buffer* pConstantBuffer);
	virtual ~UMaterialBase();

	virtual void UpdateMaterialConstantBuffer(URenderer* render, const void* pCBuffer, UINT iBufferDataSize);

	virtual void RenderDebug();

	virtual void Bind(URenderer* render);

	virtual void ReleaseMaterial();

private:
	ComPtr<ID3D11VertexShader>			m_pVertexShader = nullptr;
	ComPtr<ID3D11PixelShader>			m_pPixelShader = nullptr;

	ComPtr<ID3D11ShaderResourceView>	m_pShaderResourceViews = nullptr;
	ComPtr<ID3D11SamplerState>			m_pSamplerState = nullptr;

	ComPtr<ID3D11Buffer>				m_pConstantBuffer = nullptr ;
};

