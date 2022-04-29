#include "stdafx.h"
#include "Player.h"
#include "AbstractFactory.h"
#include "KeyMgr.h"
#include "ObjMgr.h"

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
}

int CPlayer::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	// 2. 입력을 받는다.
	Key_Input();

	Update_Rect();

	return OBJ_NOEVENT;
}

void CPlayer::Late_Update(void)
{
	CObj::UpdateGravity();

	// 3. 점프면 힘을 준다.
	if (m_bJump)
	{
		m_tInfo.fY -= m_fJumpPower * sinf((90.f * PI) / 180.f);
	}
}

void CPlayer::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	MoveToEx(hDC, m_tInfo.fX, m_tInfo.fY, nullptr);
}

void CPlayer::Release(void)
{

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

void CPlayer::OnCollision()
{
}

void CPlayer::OnCollision(DIRECTION eDir)
{
	if (DIR_UP == eDir)
	{
		m_bOnBlock = true;
		m_bJump = false;
	}
	else if (DIR_DOWN == eDir)
	{
		m_fJumpPower = 0.f;
	}
}
