#include "stdafx.h"
#include "MovingBlock.h"
#include "MainGame.h"
#include "Player.h"

#include "ScrollMgr.h"

CMovingBlock::CMovingBlock()
{
}

CMovingBlock::~CMovingBlock()
{
	Release();
}

void CMovingBlock::Initialize(void)
{
	//m_tInfo.fX = 70.f;		// 중점 X
	//m_tInfo.fY = 250.f;		// 중점 Y

	m_pPlayer = nullptr;
	m_tInfo.fCX = 64.f;
	m_tInfo.fCY = 32.f;

	m_fSpeed = 1.f;

	m_Tag = "Block";
}

int CMovingBlock::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	m_tInfo.fY -= m_fSpeed * CMainGame::m_fTime;
	if (m_pPlayer != nullptr)
	{
		if (m_tInfo.fCX > abs(m_pPlayer->Get_Info().fX - m_tInfo.fX) && m_tInfo.fCY > abs(m_pPlayer->Get_Info().fY - m_tInfo.fY))
		{
			m_pPlayer->Set_Pos(m_pPlayer->Get_Info().fX, (m_tInfo.fY - m_tInfo.fCY + 2.1));
		}
		m_pPlayer = nullptr;
	}

	Update_Rect();

	return OBJ_NOEVENT;
}

void CMovingBlock::Late_Update(void)
{
	// m_tInfo.fY에서 +-50으로 직접 설정해준 값
	if ( 200 >= m_tRect.top || 300 <= m_tRect.bottom)
		m_fSpeed *= -1.f;

	// MovingBlock을 랜덤 소환하면 그에 따라 +-50으로 설정해준 값?
	/*if (m_tInfo.fY - 50 >= m_tRect.top || m_tInfo.fY + 50 <= m_tRect.bottom)
		m_fSpeed *= -1.f;*/
}

void CMovingBlock::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top, m_tRect.right + iScrollX, m_tRect.bottom);
}

void CMovingBlock::Release(void)
{
}

void CMovingBlock::OnCollision()
{
}

void CMovingBlock::OnCollision(DIRECTION eDir)
{
}

void CMovingBlock::OnCollision(DIRECTION eDir, CObj* other)
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
