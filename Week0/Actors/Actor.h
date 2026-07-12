#pragma once
#include "../Headers.h"
#include "../Structs.h"
#include "../Enums.h"
#include "../Render/URenderer.h"
#include "../Components/ComponentBase.h"
#include "../Components/TransformComponent.h"
#include <string>

class CMesh;

class AActor
{
public:
	AActor();
	virtual ~AActor();

public:
	virtual const char* GetName() = 0;

	virtual void Init();

	virtual void Update();


	virtual void LateUpdate();

	virtual void RenderDebug();

	virtual void Release();

	virtual void Render(URenderer* renderer);

	
	CMesh*			GetMesh() { return m_pMesh; }

	FColor			GetColor() { return m_fColor; }

	

	void			SetMesh(EMeshType eMeshType);

	//void			SetPosition(FVector fPosition) { m_fPosition = fPosition; }
	//
	//void			SetVelocity(FVector fVelocity) { m_fVelocity = fVelocity; }
	//void			SetVelocity(float fVelocity);
	//void			SetSize(float scala);
	//void			SetSize(FVector fSize) { m_fSize = fSize; }
	
	void			SetColor(float color);
	void			SetColor(const FColor& color);

	UTransformComponent* const	GetTransform();

	//
	URenderer::FConstantBuffer& const GetConstantBuffer();


	template<typename T>
	T* GetComponent();

	template<typename T>
	void AddComponent(T* pComponent);

	
protected:
	static UINT		m_iRefCount;

	FColor m_fColor = FColor(1.f,1.f,1.f,1.f);

	UINT m_iIndicesCount = 0;

	CMesh* m_pMesh;

	std::string m_strName;

	URenderer::FConstantBuffer m_fCBuffer;

private:
	 std::list<UComponentBase*> m_Components;
};

