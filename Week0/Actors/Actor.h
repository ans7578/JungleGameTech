#pragma once
#include "../Headers.h"
#include "../Structs.h"
#include "../Enums.h"
#include "../Render/URenderer.h"
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

	virtual void Render(URenderer* renderer);

	
	CMesh*			GetMesh() { return m_pMesh; }
	FColor			GetColor() { return m_fColor; }

	

	void			SetMesh(EMeshType eMeshType);
	
	void			SetColor(float color);
	void			SetColor(const FColor& color);


	//
	URenderer::FConstantBuffer& const GetConstantBuffer();

	template<typename T>
	void	AddComponent(T* component);

	template<typename T>
	T* GetComponent();


	UTransformComponent* GetTransform();


	
protected:
	static UINT		m_iRefCount;

	FColor m_fColor = FColor(1.f,1.f,1.f,1.f);

	UINT m_iIndicesCount = 0;

	CMesh* m_pMesh;

	std::string m_strName;

	URenderer::FConstantBuffer m_fCBuffer;

private:
	std::list<UComponentBase*> m_components;

};
