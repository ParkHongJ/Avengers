#include "stdafx.h"
#include "Turtle.h"

#include "ScrollMgr.h"

CTurtle::CTurtle()
{
}

CTurtle::~CTurtle()
{
}

void CTurtle::Initialize()
{
	m_tInfo.fX = 400.f;
	m_tInfo.fY = 0.f;

	m_tInfo.fCX = 32.f;
	m_tInfo.fCY = 32.f;
	m_fSpeed = 0.5f;
	m_bDead = false;
	m_Tag = "Monster";
	m_eState = Idle;
}

int CTurtle::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	m_tInfo.fX -= m_fSpeed;
	Update_Rect();
	return OBJ_NOEVENT;
}

void CTurtle::Late_Update()
{
	CObj::UpdateGravity();
	//if (m_tInfo.fX <= 100 || m_tInfo.fX >= WINCX - 100)
	//{
	//	m_fSpeed *= -1.f;
	//}
}

void CTurtle::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();

	switch (m_eState)
	{
	case Idle:
		Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top, m_tRect.right + iScrollX, m_tRect.bottom);
		break;
	case Hide:
		Ellipse(hDC, m_tRect.left + iScrollX, m_tRect.top, m_tRect.right + iScrollX, m_tRect.bottom);
		break;
	default:
		break;
	}
}

void CTurtle::OnCollision(DIRECTION eDir, CObj* other)
{
	switch (eDir)
	{
	case DIR_UP:
		if (other->CompareTag("Player"))
		{
			if (m_eState == Hide)
			{
				m_fSpeed = 0.f;
			}
			else
			{
				m_eState = Hide;
				m_fSpeed = 0.f;
			}
		}
		//śĽżĄşŮąâ
		m_bOnBlock = true;
		break;
	case DIR_DOWN:
		
		break;
	case DIR_LEFT:
		if (m_eState == Hide)
		{
			m_fSpeed = -8.f;
		}
		break;
	case DIR_RIGHT:
		if (m_eState == Hide)
		{
			m_fSpeed = 8.f;
		}
		break;
	default:
		break;
	}
}


void CTurtle::Release()
{
}
