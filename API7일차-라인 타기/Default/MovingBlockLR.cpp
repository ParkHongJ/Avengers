#include "stdafx.h"
#include "MovingBlockLR.h"
#include "MainGame.h"
#include "Player.h"

#include "ScrollMgr.h"
#include "KeyMgr.h"

CMovingBlockLR::CMovingBlockLR()
	: m_bCenter_Check(false)
{
}

CMovingBlockLR::~CMovingBlockLR()
{
    Release();
}

void CMovingBlockLR::Initialize(void)
{
	m_pPlayer = nullptr;
	m_tInfo.fCX = 64.f;
	m_tInfo.fCY = 32.f;

	m_fSpeed = 1.f;
	m_iTest = 0;

	m_Tag = "Block";
	m_Sprite = IDB_FLOOR_BLOCK;
}

int CMovingBlockLR::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	if (!m_bCenter_Check)
	{
		m_fCenter_Pos = m_tInfo.fX;
		m_bCenter_Check = true;
	}
	
	m_tInfo.fX -= m_fSpeed * CMainGame::m_fTime;
	if (m_pPlayer != nullptr)
	{
		if (m_tInfo.fCX > abs(m_pPlayer->Get_Info().fX - m_tInfo.fX) && m_tInfo.fCY > abs(m_pPlayer->Get_Info().fY - m_tInfo.fY))
		{
			// 플레이어가 움직이고 있는지 판단
			if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT) || CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
			{
				m_iTest = 0;
			}
			else // 블럭x - 플레이어x + 블럭x
			{
				if (m_iTest == 0)
				{
					m_iTest = m_pPlayer->Get_Info().fX - m_tInfo.fX;
				}
				m_pPlayer->Set_Pos(m_tInfo.fX + m_iTest, m_pPlayer->Get_Info().fY);
			}
		}
		m_pPlayer = nullptr;
	}

	Update_Rect();

	return OBJ_NOEVENT;
}

void CMovingBlockLR::Late_Update(void)
{
	if ( m_fCenter_Pos - 50 >= m_tRect.left || m_fCenter_Pos + 50 <= m_tRect.right)
		m_fSpeed *= -1.f;
}

void CMovingBlockLR::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	HDC MemDC;
	HBITMAP MyBitmap, OldBitmap;
	m_tRect.right += iScrollX - 5;
	m_tRect.left += iScrollX + 5;
	MemDC = CreateCompatibleDC(hDC);

	MyBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(m_Sprite));
	OldBitmap = (HBITMAP)SelectObject(MemDC, MyBitmap);
	TransparentBlt(hDC, m_tRect.left, m_tRect.top, 32, 32, MemDC, 0, 0, 16, 16, RGB(0, 0, 0));
	SelectObject(MemDC, OldBitmap);
	DeleteObject(MyBitmap);
	DeleteDC(MemDC);
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
