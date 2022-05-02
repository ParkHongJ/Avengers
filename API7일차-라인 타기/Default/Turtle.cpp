#include "stdafx.h"
#include "Turtle.h"
#include "ObjMgr.h"
#include "ScrollMgr.h"
#include "Resource.h"
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
}

void CTurtle::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();

	switch (m_eState)
	{
	case Idle:
		m_Sprite = IDB_TURTEL_IDLE;
		break;
	case Hide:
		m_Sprite = IDB_TURTLE_HIDE;
		break;
	default:
		break;
	}

	HDC MemDC;
	HBITMAP MyBitmap, OldBitmap;
	m_tRect.right += iScrollX - 5;
	m_tRect.left += iScrollX + 5;
	MemDC = CreateCompatibleDC(hDC);

	MyBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(m_Sprite));
	OldBitmap = (HBITMAP)SelectObject(MemDC, MyBitmap);
	TransparentBlt(hDC, m_tRect.left, m_tRect.top, 32, 32, MemDC, 0, 0, 16, 16, RGB(255, 0, 0));
	SelectObject(MemDC, OldBitmap);
	DeleteObject(MyBitmap);
	DeleteDC(MemDC);
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
		/*if (m_eState == Hide)
		{
			m_fSpeed = 8.f;
		}*/
		 if (other->CompareTag("Player") && m_eState == Hide)
		{
			m_fSpeed = -8.f;
			m_eState = Spine;
		}
		else
		{
			m_fSpeed *= -1;
		}
		break;
	case DIR_RIGHT:
		/*if (m_eState == Hide)
		{
			m_fSpeed = -8.f;
		}*/
		if (other->CompareTag("Player") && m_eState == Hide)
		{
			m_fSpeed = -8.f;
			m_eState = Spine;
		}
		else if (other->CompareTag("Player") && m_eState == Spine)
		{

		}
		else
		{
			m_fSpeed *= -1;
		}
		break;
	default:
		break;
	}
}


void CTurtle::Release()
{
}
