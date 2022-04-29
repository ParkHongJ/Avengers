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

	return OBJ_NOEVENT;
}

void CMonster::Late_Update(void)
{

}

void CMonster::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CMonster::Release(void)
{

}

void CMonster::OnCollision()
{
	// m_bDead = true;
}