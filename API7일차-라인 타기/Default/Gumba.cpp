#include "stdafx.h"
#include "Gumba.h"
#include "ScrollMgr.h"
#include "MainGame.h"

CGumba::CGumba()
{
}

CGumba::~CGumba()
{
}

void CGumba::Initialize(void)
{
	m_tInfo.fX = 400.f;
	m_tInfo.fY = 0.f;
	m_tInfo.fCX = 32.f;
	m_tInfo.fCY = 32.f;
	m_fSpeed = -0.8f;
	m_bDead = false;
	m_Tag = "Monster";
}

int CGumba::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	m_tInfo.fX -= m_fSpeed * CMainGame::m_fTime;
	Update_Rect();
	return OBJ_NOEVENT;
}

void CGumba::Late_Update(void)
{
	CObj::UpdateGravity();
	if (m_tInfo.fX <= 100 || m_tInfo.fX >= WINCX - 100)
	{
		m_fSpeed *= -1.f;
	}
}

void CGumba::Render(HDC hDC)
{
	if (!m_bDead)
	{
		int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
		Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top, m_tRect.right + iScrollX, m_tRect.bottom);
	}
}

void CGumba::OnCollision(DIRECTION eDir, CObj* other)
{
	switch (eDir)
	{
	case DIR_UP:
		if (other->CompareTag("Player"))
		{
			m_bDead = true;
		}
		else
		{
			m_bOnBlock = true;
		}
		break;
	case DIR_DOWN:
		break;
	case DIR_LEFT:
		break;
	case DIR_RIGHT:
		break;
	default:
		break;
	}
}
void CGumba::Release(void)
{
}