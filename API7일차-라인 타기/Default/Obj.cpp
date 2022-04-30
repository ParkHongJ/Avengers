#include "stdafx.h"
#include "Obj.h"

CObj::CObj()
	: m_fSpeed(0.f)
	, m_eDir(DIR_END)
	, m_bDead(false)
	, m_bOnBlock(false)
	, m_bOnAir(true)
	, m_fGTime(0.f)

{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	ZeroMemory(&m_tRect, sizeof(RECT));
}

CObj::~CObj()
{

}

void CObj::Update_Rect(void)
{
	// 중심 좌표를 기준으로 left-top, right-bottom 계산
	m_tRect.left = long(m_tInfo.fX - (m_tInfo.fCX / 2.f));
	m_tRect.top = long(m_tInfo.fY - (m_tInfo.fCY / 2.f));
	m_tRect.right = long(m_tInfo.fX + (m_tInfo.fCX / 2.f));
	m_tRect.bottom = long(m_tInfo.fY + (m_tInfo.fCY / 2.f));
}

void CObj::UpdateGravity()
{
	// 1,공중이냐 바닥이냐
	
	if (m_bOnBlock)
	{// 블럭 위다
		m_bOnAir = false;
	}
	else
	{// 공중이다
		m_bOnAir = true;
	}

	// 공중이면 중력을 준다.
	if (m_bOnAir)
	{
		m_tInfo.fY -= -9.8f * m_fGTime * 0.5f;
		m_fGTime += 0.1f;
	}
	else
	{
		m_fGTime = 0.f;
	}

	m_bOnBlock = false;
}
