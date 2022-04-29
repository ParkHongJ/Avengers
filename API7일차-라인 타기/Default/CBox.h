#pragma once
#include "Obj.h"
class CBox :
    public CObj
{
public:
    virtual void Initialize() override;
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC hDC);
    virtual void Release() override;
public:
    CBox();
    ~CBox();
};

