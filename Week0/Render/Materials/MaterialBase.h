#pragma once
#include "../../Structs.h"
#include "../../Headers.h"

class URenderer;

class UMaterialBase
{
public:
	UMaterialBase() = default;

	virtual ~UMaterialBase();
	
	virtual void SetUpMaterial(weak_ptr<FShaderProgram> pShaderProgram, ID3D11ShaderResourceView* pSRV);

	virtual void UpdateMaterialConstantBuffer(URenderer* render, const void* pCBuffer, UINT iBufferDataSize);

	virtual void RenderDebug();

	virtual void Bind(URenderer* render);

	virtual void ReleaseMaterial();

protected:
	FMaterialBufferData					m_fBufferData;
private:
	weak_ptr<FShaderProgram>			m_pShaderProgram;


	ComPtr<ID3D11ShaderResourceView>	m_pShaderResourceViews = nullptr;
};

