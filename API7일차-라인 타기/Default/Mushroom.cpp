#include "stdafx.h"
#include "Mushroom.h"
#include "Player.h"
#include "ScrollMgr.h"


CMushroom::CMushroom()
{
}

CMushroom::~CMushroom()
{
	Release();
}

void CMushroom::Initialize(void)
{
	m_tInfo.fCX = 30.f;
	m_tInfo.fCY = 30.f;

	m_Tag = "Mushroom";                         //태그 추가 
}

int CMushroom::Update(void)
{
	if (m_bDead)               // 살았니 죽었니 코드 
		return OBJ_DEAD;

	Update_Rect();

	return 0;
}

void CMushroom::Late_Update(void)
{
}

void CMushroom::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top, m_tRect.right + iScrollX, m_tRect.bottom);
}

void CMushroom::Release(void)
{
}

void CMushroom::OnCollision(CObj* other)
{
	Set_Dead();                                      //죽어서
	if (other->CompareTag("Player"))                 //플레이어 크기 커지는 코드
	{
		dynamic_cast<CPlayer*>(other)->UpLife();
	}
}
