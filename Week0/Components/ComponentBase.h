#pragma once

class URenderer;

class UComponentBase
{
public :
	UComponentBase() = default;
	virtual ~UComponentBase() = default;


public:
	virtual void Init_Component() = 0;
	
	virtual void Update_Component() = 0;
	
	virtual void LateUpdate_Component() = 0;

	virtual void RenderDebug_Component() = 0;

	virtual void Render_Component(URenderer* renderer) = 0;

	virtual void Release_Component() = 0;

	virtual const char* GetComponentName() = 0;

};

