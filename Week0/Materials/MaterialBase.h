#pragma once
#include "../Structs.h"
#include "../Headers.h"

class URenderer;

class UMaterialBase
{
public:
	UMaterialBase();

	virtual ~UMaterialBase();
	
	virtual HRESULT Init();

	virtual void AddTexture(ComPtr<ID3D11ShaderResourceView> pSRV);

	virtual void UpdateMaterialConstantBuffer(URenderer* render, const void* pCBuffer, UINT iBufferDataSize);

	virtual void RenderDebug();

	virtual void Bind(URenderer* render) = 0;

	virtual void ReleaseMaterial();

	virtual const wchar_t* GetMaterialName() = 0;

protected:
	FMaterialBufferData					m_fBufferData;

	weak_ptr<FShaderProgram>			m_pShaderProgram;

	vector<ComPtr<ID3D11ShaderResourceView>> m_pShaderResourceViews;
};

