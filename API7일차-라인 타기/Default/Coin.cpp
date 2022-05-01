#include "stdafx.h"
#include "Coin.h"

#include "ScrollMgr.h"

CCoin::CCoin()
{
}

CCoin::~CCoin()
{
	Release();
}

void CCoin::Initialize(void)
{


	m_tInfo.fX = 600.f;		// 중점 X
	m_tInfo.fY = 300.f;		// 중점 Y

	m_tInfo.fCX = 50.f;
	m_tInfo.fCY = 50.f;
}

int CCoin::Update(void)
{
	if (m_bDead)               // 살았니 죽었니 코드 
		return OBJ_DEAD;

	
	Update_Rect();
	return 0;
}

void CCoin::Late_Update(void)
{
}

void CCoin::Render(HDC hDC)
{
	int iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top, m_tRect.right + iScrollX, m_tRect.bottom);
}
void CCoin::Release(void)
{

}

void CCoin::OnCollision()
{
	
}

void CCoin::OnCollision(DIRECTION eDir, CObj* other)
{
	Set_Dead();
}
