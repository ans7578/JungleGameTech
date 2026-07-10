#pragma once
#include "Actor.h"
class ABoundActor :
    public AActor
{
public:
    ABoundActor();

    virtual ~ABoundActor();


public:
    virtual void Update() override;


    // AActor을(를) 통해 상속됨
    virtual const char* GetName() override;

};

