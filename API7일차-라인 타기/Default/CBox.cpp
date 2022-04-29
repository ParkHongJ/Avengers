#include "stdafx.h"
#include "CBox.h"
#include "ScrollMgr.h"

void CBox::Initialize()
{
    m_tInfo.fX = 400.f;
    m_tInfo.fY = 300.f;

    m_tInfo.fCX = 16.f;
    m_tInfo.fCY = 16.f;
    m_Tag = "Box";
}

int CBox::Update()
{

    Update_Rect();
    return OBJ_NOEVENT;
}

void CBox::Late_Update()
{
}

void CBox::Render(HDC hDC)
{
    int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
    Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top, m_tRect.right + iScrollX, m_tRect.bottom);
}

void CBox::Release()
{
}

CBox::CBox()
{
}

CBox::~CBox()
{
}
