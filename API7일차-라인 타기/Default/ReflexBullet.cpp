#include "stdafx.h"
#include "ReflexBullet.h"

#include "ScrollMgr.h"


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

	m_fSpeed = 5.f;
	m_bIsBouns = false;
}

int CReflexBullet::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	m_tInfo.fX += m_fSpeed * cosf((m_fAngle * PI) / 180.f);
	m_tInfo.fY -= m_fSpeed * sinf((m_fAngle * PI) / 180.f);


	Update_Rect();
	return OBJ_NOEVENT;
}

void CReflexBullet::Late_Update(void)
{

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
	//if (m_bIsBouns)
	//	return;
	//m_bIsBouns = true;
	
	m_fAngle = 360.f - m_fAngle;

	switch (eDir)
	{
	case DIR_LEFT:
		m_fAngle += 180.f;
		break;
	case DIR_UP:
		break;
	case DIR_RIGHT:
		break;
	case DIR_DOWN:
		break;
	}
}
