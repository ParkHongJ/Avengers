#pragma once
#include "Obj.h"
#include "Line.h"
class CTile :
    public CObj
{
public:
    CTile();
    ~CTile();

public:
    virtual void Initialize() override;
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;
private:
    int m_iSpriteNum;
    CLine* m_Line;
    int m_iSize;

};

