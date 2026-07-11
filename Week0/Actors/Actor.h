#pragma once
#include "../Headers.h"
#include "../Structs.h"
#include "../Enums.h"
#include "../Render/URenderer.h"
#include <string>

class CMesh;


class AActor
{
public:
	AActor();
	virtual ~AActor();

public:
	virtual const char* GetName() = 0;

	virtual void Update();


	virtual void LateUpdate();

	virtual void RenderDebug();

	virtual void Render(URenderer* renderer);

	
	CMesh*			GetMesh() { return m_pMesh; }
	FVector			GetPosition() { return m_fPosition; }
	FVector			GetVelocity() { return m_fVelocity; }
	FVector			GetSize() { return m_fSize; }
	FColor			GetColor() { return m_fColor; }

	

	void			SetMesh(EMeshType eMeshType);

	void			SetPosition(FVector fPosition) { m_fPosition = fPosition; }

	void			SetVelocity(FVector fVelocity) { m_fVelocity = fVelocity; }
	void			SetVelocity(float fVelocity);


	void			SetSize(float scala);
	void			SetSize(FVector fSize) { m_fSize = fSize; }
	
	void			SetColor(float color);
	void			SetColor(const FColor& color);


	//
	URenderer::FConstantBuffer& const GetConstantBuffer();


	
protected:
	static UINT		m_iRefCount;

	FVector m_fPosition = FVector(0.f,0.f,0.f);
	FVector m_fVelocity = FVector(0.f, 0.f, 0.f);
	FVector m_fSize = FVector(1.f, 1.f, 1.f);

	FColor m_fColor = FColor(1.f,1.f,1.f,1.f);

	UINT m_iIndicesCount = 0;

	CMesh* m_pMesh;

	std::string m_strName;

	URenderer::FConstantBuffer m_fCBuffer;

};

