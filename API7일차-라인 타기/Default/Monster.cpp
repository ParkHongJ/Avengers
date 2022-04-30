#include "stdafx.h"
#include "Monster.h"


CMonster::CMonster()
{
}

CMonster::~CMonster()
{
	Release();
}

void CMonster::Initialize(void)
{
	m_tInfo.fX = 600.f;		// 중점 X
	m_tInfo.fY = 300.f;		// 중점 Y

	m_tInfo.fCX = 32.f;
	m_tInfo.fCY = 32.f;

	m_fSpeed = 1.f;

	m_eDir = DIR_LEFT;
	m_tItemInfo.fX = 256.f;
	m_tItemInfo.fY = 300.f;

	m_tItemInfo.fCX = 32.f;
	m_tItemInfo.fCY = 32.f;
}

int CMonster::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	//double dX = m_pTarget->Get_Info().fX - m_tInfo.fX;
	//double dY = m_pTarget->Get_Info().fY - m_tInfo.fY;

	// acos를 사용해서 0~180 사이의 각도 구하기
	//float dis = sqrt((dX * dX) + (dY * dY));
	//m_fAngle = acosf(dX / dis);

	// 플레이어가 몬스터보다 아래에 있다면 각도를 반전해 준다.
	//if (m_pTarget->Get_Info().fY > m_tInfo.fY)  // (윈도우 좌표계)
	//	m_fAngle *= -1.f;

	// 윈도우 좌표계이기때문에 y는 빼준다.
	//m_tInfo.fX += m_fSpeed * cosf(m_fAngle);
	//m_tInfo.fY -= m_fSpeed * sinf(m_fAngle);


	Update_Rect();
	//if(아이템이 활성화 되어있나?) -> 이거는 아이템말고 블럭활성화로 바꾸는게 좋을듯
	if (m_tItemInfo.fY >= m_tInfo.fY - 32.f)
	{
		m_tItemInfo.fY -= m_fItemSpeed;
	}
	//item->Update_ItemRect() 
	m_tItemRect.left = long(m_tItemInfo.fX - (m_tItemInfo.fCX / 2.f));
	m_tItemRect.top = long(m_tItemInfo.fY - (m_tItemInfo.fCY / 2.f));
	m_tItemRect.right = long(m_tItemInfo.fX + (m_tItemInfo.fCX / 2.f));
	m_tItemRect.bottom = long(m_tItemInfo.fY + (m_tItemInfo.fCY / 2.f));
	return OBJ_NOEVENT;
}

void CMonster::Late_Update(void)
{

}

void CMonster::Render(HDC hDC)
{

	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	Ellipse(hDC, m_tItemRect.left, m_tItemRect.top, m_tItemRect.right, m_tItemRect.bottom);
}

void CMonster::Release(void)
{

}

void CMonster::OnCollision(DIRECTION eDir, CObj* other)
{
	switch (eDir)
	{
	case DIR_DOWN:
		m_fItemSpeed = 1.f;
		break;
	}
}

void CMonster::OnCollision()
{
}
