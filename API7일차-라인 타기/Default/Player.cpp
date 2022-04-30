#include "stdafx.h"
#include "Player.h"
#include "AbstractFactory.h"
#include "KeyMgr.h"
#include "ObjMgr.h"
#include "LineMgr.h"
#include "ScrollMgr.h" 
#include "MainGame.h"
CPlayer::CPlayer()
{
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize(void)
{
	m_tInfo.fX = 400.f;
	m_tInfo.fY = 0.f;

	m_tInfo.fCX = 16.f;
	m_tInfo.fCY = 32.f;

	m_fSpeed = 5.f;

	m_bJump = false;
	m_fJumpPower = 10.f;
	m_Tag = "Player";
}

int CPlayer::Update(void)
{
	if (m_bDead || m_tInfo.fY >= WINCY)
		return OBJ_DEAD;
	Key_Input();

	Update_Rect();

	return OBJ_NOEVENT;
}

void CPlayer::Late_Update(void)
{
	CObj::UpdateGravity();
	if (m_bJump)
	{
		m_tInfo.fY -= m_fJumpPower * sinf((90.f * PI) / 180.f);
	}
}

void CPlayer::Render(HDC hDC)
{
	// Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	//MoveToEx(hDC, m_tInfo.fX, m_tInfo.fY, nullptr);
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	//Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top, m_tRect.right + iScrollX, m_tRect.bottom);

	// // ���� �׸���
	// MoveToEx(hDC, (int)m_tInfo.fX + iScrollX, (int)m_tInfo.fY, nullptr);
	// LineTo(hDC, (int)m_tPosin.x + iScrollX, (int)m_tPosin.y);

	/*if (m_bAbility)
	{
		MoveToEx(hDC, (int)m_tInfo.fX + iScrollX, (int)m_tInfo.fY, nullptr);
		POINT mouse = {};
		GetCursorPos(&mouse);
		ScreenToClient(g_hWnd, &mouse);
		LineTo(hDC, (int)mouse.x, (int)mouse.y);
	}*/
	
}



void CPlayer::Key_Input(void)
{
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
	{
		m_tInfo.fX -= m_fSpeed;
		//CScrollMgr::Get_Instance()->Set_ScrollX(m_fSpeed);
	}
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
	{
		m_tInfo.fX += m_fSpeed;
		//CScrollMgr::Get_Instance()->Set_ScrollX(-m_fSpeed);
	}
	if (CKeyMgr::Get_Instance()->Key_Down('V'))
	{
		//시간정지
		CMainGame::m_fTime = 0.1f;
	}
	if (CKeyMgr::Get_Instance()->Key_Down(VK_DOWN))
	{
		m_tInfo.fCY = 16.f;
	}
	
	// Jump
	if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE) && !m_bJump)
	{
		m_fJumpPower = 10.f;
		m_bJump = true;
		return;
	}

	if (MAPSIZE_LEFT >= m_tInfo.fX)
		m_tInfo.fX = MAPSIZE_LEFT;
	else if (MAPSIZE_RIGHT <= m_tInfo.fX)
		m_tInfo.fX = MAPSIZE_RIGHT;
}

void CPlayer::OnCollision(DIRECTION eDir, CObj* other)
{
	switch (eDir)
	{
	case DIR_UP:
	
		if (other->CompareTag("Monster"))
		{
			m_fJumpPower *= 0.9f;
			m_fGTime = 0.f;
		}
		else
		{
			m_bOnBlock = true;
			m_bJump = false;
		}
		break;
	case DIR_DOWN:
		m_fJumpPower = 0.f;
		break;
	case DIR_LEFT:
		if (other->CompareTag("Monster"))
		{
			//PostQuitMessage(0);
		}
		break;
	case DIR_RIGHT:
		if (other->CompareTag("Monster"))
		{
			//PostQuitMessage(0);
		}
		break;
	default:
		break;
	}
}

void CPlayer::OffSet(void)
{
	int		iOffSetX = WINCX >> 1;
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iItv = 300;


	if (iOffSetX - iItv > m_tInfo.fX + iScrollX)
		CScrollMgr::Get_Instance()->Set_ScrollX(m_fSpeed);

	if (iOffSetX + iItv < m_tInfo.fX + iScrollX)
		CScrollMgr::Get_Instance()->Set_ScrollX(-m_fSpeed);
}

void CPlayer::OnCollision()
{
}

void CPlayer::OnCollision(DIRECTION eDir)
{
}

void CPlayer::Release(void)
{

}
