#include "stdafx.h"
#include "MovingBlock.h"
#include "MainGame.h"
#include "Player.h"
#include "Resource.h"
#include "ScrollMgr.h"

CMovingBlock::CMovingBlock()
	: m_bCenter_Check(false)
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
	m_tInfo.fCX = 32.f;
	m_tInfo.fCY = 32.f;

	m_fSpeed = 1.f;

	m_Tag = "Block";
	m_Sprite = IDB_FLOOR_BLOCK;
}

int CMovingBlock::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	if (!m_bCenter_Check)
	{
		m_fCenter_Pos = m_tInfo.fY;
		m_bCenter_Check = true;
	}

	m_tInfo.fY -= m_fSpeed * CMainGame::m_fTime;
	if (m_pPlayer != nullptr)
	{
		if (m_tInfo.fCX >= abs(m_pPlayer->Get_Info().fX - m_tInfo.fX) && m_tInfo.fCY >= abs(m_pPlayer->Get_Info().fY - m_tInfo.fY))
		{
			m_pPlayer->Set_Pos(m_pPlayer->Get_Info().fX, (m_tInfo.fY - m_tInfo.fCY + 2.2f));
		}
		m_pPlayer = nullptr;
	}
	
	Update_Rect();

	return OBJ_NOEVENT;
}

void CMovingBlock::Late_Update(void)
{
	if (m_fCenter_Pos - 50 >= m_tRect.top || m_fCenter_Pos + 50 <= m_tRect.bottom)
		m_fSpeed *= -1.f;
}

void CMovingBlock::Render(HDC hDC)
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
