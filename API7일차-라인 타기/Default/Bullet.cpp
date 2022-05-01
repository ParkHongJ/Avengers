#include "stdafx.h"
#include "Bullet.h"
#include "MainGame.h"


CBullet::CBullet()
{
}


CBullet::~CBullet()
{
	Release();
}

void CBullet::Initialize(void)
{
	m_tInfo.fCX = 50.f;
	m_tInfo.fCY = 50.f;

	m_fSpeed = 2.f;
	m_bDown = false;
}

int CBullet::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	if (!m_bDown)
	{
		m_tInfo.fX += CMainGame::m_fTime * m_fSpeed * cosf((m_fAngle * PI) / 180.f);
		m_tInfo.fY -= CMainGame::m_fTime * m_fSpeed * sinf((m_fAngle * PI) / 180.f);
	}
	else
	{
		m_tInfo.fY += CMainGame::m_fTime * m_fSpeed * sinf((m_fAngle * PI) / 180.f);
	}
	
	Update_Rect();

	return OBJ_NOEVENT;
}

void CBullet::Late_Update(void)
{

	if (m_tInfo.fY >= WINCY + 50)
	{
		m_bDead = true;
	}
	if (m_tInfo.fY <= -400)
	{
		m_fSpeed *= -1;
		m_fAngle = -90.f;
		m_tInfo.fY = -1 * (rand() % (350 + 1 - 100) + 100);
		m_tInfo.fX = rand() % (WINCX + 1);
		m_bDown = true;
	}
}

void CBullet::Render(HDC hDC)
{
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CBullet::Release(void)
{
	
}
