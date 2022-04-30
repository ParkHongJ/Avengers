#include "stdafx.h"
#include "MovingBlock.h"

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
	//m_tInfo.fX = 70.f;		// ���� X
	//m_tInfo.fY = 250.f;		// ���� Y

	m_tInfo.fCX = 64.f;
	m_tInfo.fCY = 32.f;

	m_fSpeed = 1.f;
}

int CMovingBlock::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	m_tInfo.fY -= m_fSpeed;

	Update_Rect();

	return OBJ_NOEVENT;
}

void CMovingBlock::Late_Update(void)
{
	// m_tInfo.fY���� +-50���� ���� �������� ��
	if ( 200 >= m_tRect.top || 300 <= m_tRect.bottom)
		m_fSpeed *= -1.f;

	// MovingBlock�� ���� ��ȯ�ϸ� �׿� ���� +-50���� �������� ��?
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
