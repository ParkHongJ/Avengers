#include "stdafx.h"
#include "Coin.h"

CCoin::CCoin()
{
}

CCoin::~CCoin()
{
	Release();
}

void CCoin::Initialize(void)
{


	m_tInfo.fX = 600.f;		// ���� X
	m_tInfo.fY = 300.f;		// ���� Y

	m_tInfo.fCX = 50.f;
	m_tInfo.fCY = 50.f;
}

int CCoin::Update(void)
{
	if (m_bDead)               // ��Ҵ� �׾��� �ڵ� 
		return OBJ_DEAD;

	
	Update_Rect();
	return 0;
}

void CCoin::Late_Update(void)
{
}

void CCoin::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}
void CCoin::Release(void)
{

}

void CCoin::OnCollision()
{
	
}

void CCoin::OnCollision(DIRECTION eDir)
{
	Set_Dead();
}
