#include "stdafx.h"
#include "Timeitem.h"
#include "GameMgr.h"
#include "ScrollMgr.h"

CTimeitem::CTimeitem()
{
}

CTimeitem::~CTimeitem()
{
	Release();
}

void CTimeitem::Initialize(void)
{
	m_tInfo.fCX = 30.f;
	m_tInfo.fCY = 30.f;

}

int CTimeitem::Update(void)
{
	if (m_bDead)               // 살았니 죽었니 코드 
		return OBJ_DEAD;

	if (m_tInfo.fY >= m_itembox_y)
	{
		--m_tInfo.fY;
	}

	Update_Rect();
	return 0;
}

void CTimeitem::Late_Update(void)
{
}

void CTimeitem::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top, m_tRect.right + iScrollX, m_tRect.bottom);
}

void CTimeitem::Release(void)
{
}

void CTimeitem::OnCollision(CObj* other)
{
	Set_Dead();                                //죽었을떄 GameManager의 시간을 군바의 시간을 바꿔요 
	CGameMgr::Get_Instance()->Set_Time(0.1);

}
