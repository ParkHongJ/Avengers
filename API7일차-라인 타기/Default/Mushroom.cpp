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

	m_Tag = "Mushroom";                         //�±� �߰� 
}

int CMushroom::Update(void)
{
	if (m_bDead)               // ��Ҵ� �׾��� �ڵ� 
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
	Set_Dead();                                      //�׾
	if (other->CompareTag("Player"))                 //�÷��̾� ũ�� Ŀ���� �ڵ�
	{
		dynamic_cast<CPlayer*>(other)->UpLife();
	}
}
