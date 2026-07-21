#pragma once
#include "../Headers.h"
#include "../Structs.h"
#include "../Enums.h"
#include "../Render/URenderer.h"
#include "../Components/ComponentBase.h"
#include "../Components/TransformComponent.h"
#include <string>

class CMesh;
class UMaterialBase;



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

	FColor			GetColor() { return m_fColor; }

	EActorType		GetActorType() { return m_eActorType; }


	void			SetColor(float color);
	void			SetColor(const FColor& color);

	UTransformComponent* const	GetTransform();

	template<typename T>
	T* GetComponent()
	{
		for (UComponentBase* component : m_Components)
		{
			T* targetComponent = dynamic_cast<T*>(component);

			if (targetComponent != nullptr)
			{
				return targetComponent;
			}
		}

		return nullptr;
	}

	template<typename T>
	void AddComponent(T* pComponent)
	{
		m_Components.push_back(pComponent);
	}

	
protected:
	static UINT		m_iRefCount;

	FColor m_fColor = FColor(1.f,1.f,1.f,1.f);

	UINT m_iIndicesCount = 0;

	std::string m_strName;

	EActorType	m_eActorType;
private:
	URenderer::FWorldBufferData m_fCBufferData;
	std::list<UComponentBase*> m_Components;



};

