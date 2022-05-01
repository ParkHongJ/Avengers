#include "stdafx.h"
#include "ReflexBullet.h"

#include "ScrollMgr.h"
#include "Player.h"


CReflexBullet::CReflexBullet()
{
}


CReflexBullet::~CReflexBullet()
{
	Release();
}


void CReflexBullet::Initialize(void)
{
	m_tInfo.fCX = 10.f;
	m_tInfo.fCY = 10.f;
	m_iBounceCount = 0;
	m_fOldTime = GetTickCount64();

	m_iMaxBounceCount = 3;
	m_fLifeTime = 4000.f;
	m_fSpeed = 4.f;
	m_bIsBounce = false;
}

int CReflexBullet::Update(void)
{
	m_bIsBounce = false;
	if (m_bDead)
		return OBJ_DEAD;

	m_tInfo.fX += m_fSpeed * cosf((m_fAngle * PI) / 180.f);
	m_tInfo.fY -= m_fSpeed * sinf((m_fAngle * PI) / 180.f);

	Update_Rect();
	return OBJ_NOEVENT;
}

void CReflexBullet::Late_Update(void)
{
	if (m_iMaxBounceCount < m_iBounceCount)
	{
		((CPlayer*)Get_Target())->Set_RelexBulletToNull();
		Set_Dead();
	}
	else if (m_fOldTime + m_fLifeTime < GetTickCount64())
	{
		((CPlayer*)Get_Target())->Set_RelexBulletToNull();
		Set_Dead();
	}
}

void CReflexBullet::Render(HDC hDC)
{
	int iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	Ellipse(hDC, m_tRect.left + iScrollX, m_tRect.top, m_tRect.right + iScrollX, m_tRect.bottom);
}

void CReflexBullet::Release(void)
{

}

void CReflexBullet::OnCollision(DIRECTION eDir, CObj* other)
{
	if (other->CompareTag("Block"))
		Reflex(eDir);

}

void CReflexBullet::Reflex(DIRECTION eDir)
{
	if (m_bIsBounce)
		return;
	m_bIsBounce = true;
	++m_iBounceCount;
	
	m_fAngle = 360.f - m_fAngle;

	switch (eDir)
	{
	case DIR_LEFT:
		m_fAngle += 180.f;
		break;
	case DIR_RIGHT:
		m_fAngle -= 180.f;
		break;
	}
}
