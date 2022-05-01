#include "stdafx.h"
#include "Player.h"
#include "AbstractFactory.h"

#include "KeyMgr.h"
#include "ObjMgr.h"
#include "LineMgr.h"

#include "ScrollMgr.h" 
#include "MainGame.h"
#include "ReflexBullet.h"

CPlayer::CPlayer()
{
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize(void)
{
	m_pRelexBullet = nullptr;
	m_tInfo.fX = 400.f;
	m_tInfo.fY = 0.f;

	m_tInfo.fCX = 16.f;
	m_tInfo.fCY = 32.f;

	m_fSpeed = 5.f;

	m_bSniperMode = false;
	m_bJump = false;
	m_fJumpPower = 10.f;

	m_Tag = "Player";
	m_fGravity = 9.8f;

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

	CObj::UpdateGravity(m_fGravity);

	if (m_bJump)
	{
		m_tInfo.fY -= m_fJumpPower * sinf((90.f * PI) / 180.f);
	}
}

void CPlayer::Render(HDC hDC)
{

	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top, m_tRect.right + iScrollX, m_tRect.bottom);

	SniperRender(hDC);
}

void CPlayer::SniperRender(HDC hDC)
{
	if (!m_bSniperMode)
		return;

	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();

	m_tPosin.x = long(m_tInfo.fX + 30.f * cosf((m_fAngle * PI) / 180.f));
	m_tPosin.y = long(m_tInfo.fY - 30.f * sinf((m_fAngle * PI) / 180.f));

	MoveToEx(hDC, (int)m_tInfo.fX + iScrollX, (int)m_tInfo.fY, nullptr);
	LineTo(hDC, (int)m_tPosin.x + iScrollX, (int)m_tPosin.y);
}


void CPlayer::Key_Input(void)
{
	// SnipingMode
	if (CKeyMgr::Get_Instance()->Key_Pressing('R') && m_pRelexBullet)
	{
		m_tInfo.fX = m_pRelexBullet->Get_Info().fX;
		m_tInfo.fY = m_pRelexBullet->Get_Info().fY;
		m_pRelexBullet->Set_Dead();
		m_pRelexBullet = nullptr;
	}
	// Sniping
	if (CKeyMgr::Get_Instance()->Key_Up('W') && m_bSniperMode && !m_pRelexBullet)
	{
		m_bSniperMode = false;
		m_pRelexBullet = CAbstractFactory<CReflexBullet>::Create(m_tInfo.fX, m_tInfo.fY, m_fAngle);
		m_pRelexBullet->Set_Target(this);
		CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, m_pRelexBullet);
	}
	// SnipingMode
	if (CKeyMgr::Get_Instance()->Key_Pressing('W') && !m_pRelexBullet)
	{
		m_bSniperMode = true;

		if (CKeyMgr::Get_Instance()->Key_Pressing('Q'))
			m_fAngle += 1.5f;
		if (CKeyMgr::Get_Instance()->Key_Pressing('E'))
			m_fAngle -= 1.5f;
	}
	if (CKeyMgr::Get_Instance()->Key_Down('V'))
	{
		if (CMainGame::m_fTime == 0.1f)
			CMainGame::m_fTime = 1.f;
		else
			CMainGame::m_fTime = 0.1f;
	}
	if (CKeyMgr::Get_Instance()->Key_Down(VK_DOWN))
	{
		if (m_bJump && m_tInfo.fY <= 300.f)
		{
			m_fGravity = 15.f;
		}
	}
	
	if (CKeyMgr::Get_Instance()->Key_Down('B'))
	{
		m_fJumpPower = 5.f;
		m_fGTime = 0.f;
		m_bJump = true;
	}
	// Jump
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_SPACE) && !m_bJump)
	{
		m_fJumpPower = 10.f;
		m_bJump = true;
	}

	// Move
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
		m_tInfo.fX -= m_fSpeed;
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
		m_tInfo.fX += m_fSpeed;


	// Limit Player Pos in MapSize
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
			m_fGravity = 9.8f;
		}
		else
		{
			m_bOnBlock = true;
			m_bJump = false;
			m_fGravity = 9.8f;
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
