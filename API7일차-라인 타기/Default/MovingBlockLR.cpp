#include "stdafx.h"
#include "MovingBlockLR.h"
#include "MainGame.h"
#include "Player.h"

#include "ScrollMgr.h"

CMovingBlockLR::CMovingBlockLR()
{
}

CMovingBlockLR::~CMovingBlockLR()
{
    Release();
}

void CMovingBlockLR::Initialize(void)
{
	m_tInfo.fCX = 64.f;
	m_tInfo.fCY = 32.f;

	m_fSpeed = 1.f;

	m_Tag = "Block";
}

int CMovingBlockLR::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	m_tInfo.fX -= m_fSpeed * CMainGame::m_fTime;
	if (m_pPlayer != nullptr)
	{
		if (m_tInfo.fCX > abs(m_pPlayer->Get_Info().fX - m_tInfo.fX) && m_tInfo.fCY > abs(m_pPlayer->Get_Info().fY - m_tInfo.fY))
		{
			m_pPlayer->Set_Pos(m_pPlayer->Get_Info().fX, m_pPlayer->Get_Info().fY);
		}
		m_pPlayer = nullptr;
	}

	Update_Rect();

	return OBJ_NOEVENT;
}

void CMovingBlockLR::Late_Update(void)
{
	if ( 200 >= m_tRect.left || 300 <= m_tRect.right)
		m_fSpeed *= -1.f;
}

void CMovingBlockLR::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top, m_tRect.right + iScrollX, m_tRect.bottom);
}

void CMovingBlockLR::Release(void)
{
}

void CMovingBlockLR::OnCollision()
{
}

void CMovingBlockLR::OnCollision(DIRECTION eDir)
{
}

void CMovingBlockLR::OnCollision(DIRECTION eDir, CObj* other)
{
	switch (eDir)
	{
	case DIR_UP:
		if (other->CompareTag("Player"))
		{
			m_pPlayer = other;
		}
		break;
	}
}
