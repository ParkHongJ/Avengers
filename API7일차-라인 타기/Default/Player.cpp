#include "stdafx.h"
#include "Player.h"
#include "AbstractFactory.h"
#include "KeyMgr.h"
#include "ObjMgr.h"
#include "LineMgr.h"
#include "ScrollMgr.h"
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

	m_tInfo.fCX = 32.f;
	m_tInfo.fCY = 32.f;

	m_fSpeed = 5.f;

	m_bJump = false;
	m_fJumpPower = 10.f;
	//hong
	// m_tInfo.fCX = 16.f;
	// m_tInfo.fCY = 16.f;

	// m_fSpeed = 3.f;
	
	// m_fDiagonal = 100.f;

	// m_bJump = false;
	// m_fJumpPower = 15.f;
	// m_fJumpTime = 0.f;
	// m_bOnGrounded = false;
	// m_bAbility = false;
	// m_bDBJump = false;
	// m_iJumpCount = 0;
	// m_bDrawAbility = false;
	// temp = 1;
	// m_bOnAir = true;
}

int CPlayer::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	// 2. �Է��� �޴´�.
	Key_Input();
	//Jumping();
	
	//OffSet();

	Update_Rect();

	return OBJ_NOEVENT;
}

void CPlayer::Late_Update(void)
{
	CObj::UpdateGravity();

	// 3. ������ ���� �ش�.
	if (m_bJump)
	{
		m_tInfo.fY -= m_fJumpPower * sinf((90.f * PI) / 180.f);
	}
}

void CPlayer::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	//MoveToEx(hDC, m_tInfo.fX, m_tInfo.fY, nullptr);
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	// Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top, m_tRect.right + iScrollX, m_tRect.bottom);

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
		m_tInfo.fX -= m_fSpeed;
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
		m_tInfo.fX += m_fSpeed;

	// Jump
	if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE) && !m_bJump)
	{
		m_fJumpPower = 10.f;
		m_bJump = true;
		return;
	}
}

void CPlayer::OnCollision(DIRECTION eDir)
{
	switch (eDir)
	{
	case DIR_UP:
		m_bOnBlock = true;
		m_bJump = false;
		break;
	case DIR_DOWN:
		m_fJumpPower = 0.f;
		break;
	case DIR_LEFT:
		break;
	case DIR_RIGHT:
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

void CPlayer::Release(void)
{

}
