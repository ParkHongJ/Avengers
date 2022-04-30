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
	// �߽� ��ǥ�� �������� left-top, right-bottom ���
	m_tRect.left = long(m_tInfo.fX - (m_tInfo.fCX / 2.f));
	m_tRect.top = long(m_tInfo.fY - (m_tInfo.fCY / 2.f));
	m_tRect.right = long(m_tInfo.fX + (m_tInfo.fCX / 2.f));
	m_tRect.bottom = long(m_tInfo.fY + (m_tInfo.fCY / 2.f));
}

void CObj::UpdateGravity()
{
	// 1,�����̳� �ٴ��̳�
	
	if (m_bOnBlock)
	{// �� ����
		m_bOnAir = false;
	}
	else
	{// �����̴�
		m_bOnAir = true;
	}

	// �����̸� �߷��� �ش�.
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
