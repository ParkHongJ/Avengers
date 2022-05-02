#pragma once
#include "Obj.h"
enum State
{
    Idle = 0, //껍데기 밖에있을때
    Hide
};
class CTurtle :
    public CObj
{
public:
    CTurtle();
    ~CTurtle();
public:
    virtual void Initialize() override;
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC hDC) override;
    void OnCollision(DIRECTION eDir, CObj* other);
    virtual void Release() override;

private:
    State m_eState;
    int m_Sprite;
};

