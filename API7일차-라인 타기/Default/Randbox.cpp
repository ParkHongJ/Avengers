#include "stdafx.h"
#include "Randbox.h"

CRandbox::CRandbox()
{
}

CRandbox::~CRandbox()
{
	Release();
}

void CRandbox::Initialize(void)
{
	m_tInfo.fX = 600.f;		// 중점 X
	m_tInfo.fY = 300.f;		// 중점 Y

	m_tInfo.fCX = 32.f;
	m_tInfo.fCY = 32.f;

	m_Tag = "Randbox";
}

int CRandbox::Update(void)
{



	if (m_bDead)
		return OBJ_DEAD;

	Update_Rect();

	return 0;
}

void CRandbox::Late_Update(void)
{
}

void CRandbox::Render(HDC hDC)
{
	int iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top, m_tRect.right + iScrollX, m_tRect.bottom);
}

void CRandbox::Release(void)
{
}

void CRandbox::OnCollision(DIRECTION eDir, CObj* other)
{
	int irand = rand() % 3;



	if (m_bCheck == true)
	{
		return;
	}
	else
	{
		switch (eDir)
		{
		case DIR_DOWN:
			switch (irand)
			{
			case 0:
				CObjMgr::Get_Instance()->Add_Object(OBJ_COIN, CAbstractFactory<CCoin>::Create(m_tInfo.fX, m_tInfo.fY, true));
				m_bCheck = true;
				break;
			case 1:
				CObjMgr::Get_Instance()->Add_Object(OBJ_MUSHROOM, CAbstractFactory<CMushroom>::Create(m_tInfo.fX, m_tInfo.fY, true));
				m_bCheck = true;

				break;
			case 2:
				CObjMgr::Get_Instance()->Add_Object(OBJ_COIN, CAbstractFactory<CTimeitem>::Create(m_tInfo.fX, m_tInfo.fY, true));
				break;
			}
			break;
		}

	}













	


	
}