#include "stdafx.h"
#include "CTile.h"
#include "LineMgr.h"

CTile::CTile()
{
}

CTile::~CTile()
{
}

void CTile::Initialize()
{
    m_Line = new CLine;
    m_tInfo.fX = 400.f;
    m_tInfo.fY = 300.f;

    m_tInfo.fCX = 40.f;
    m_tInfo.fCY = 40.f;
    /*m_Line->tLPoint.fX = m_tInfo.fX - m_tInfo.fCX * 0.5f;
    m_Line->tLPoint.fY = m_tInfo.fY - m_tInfo.fCX * 0.5f;

    m_Line->tRPoint.fX = m_tInfo.fX + m_tInfo.fCX * 0.5f;
    m_Line->tRPoint.fY = m_tInfo.fY - m_tInfo.fCX * 0.5f;*/
    CLineMgr::Get_Instance()->Add_Line(m_Line);
}

int CTile::Update()
{
    Update_Rect();
    return 0;
}

void CTile::Late_Update()
{
}

void CTile::Render(HDC hDC)
{
    Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CTile::Release()
{
}
