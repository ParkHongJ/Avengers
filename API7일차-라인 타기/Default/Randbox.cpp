#include "stdafx.h"
#include "Randbox.h"
#include "Resource.h"
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
	m_Sprite = IDB_RANDOM_BLOCK;
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
	HDC MemDC;
	HBITMAP MyBitmap, OldBitmap;
	m_tRect.right += iScrollX - 5;
	m_tRect.left += iScrollX + 5;
	MemDC = CreateCompatibleDC(hDC);

	MyBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(m_Sprite));
	OldBitmap = (HBITMAP)SelectObject(MemDC, MyBitmap);
	TransparentBlt(hDC, m_tRect.left, m_tRect.top, 32, 32, MemDC, 0, 0, 16, 16, RGB(255, 255, 255));
	SelectObject(MemDC, OldBitmap);
	DeleteObject(MyBitmap);
	DeleteDC(MemDC);
}

void CRandbox::Release(void)
{
}

void CRandbox::OnCollision(DIRECTION eDir, CObj* other)
{
	int irand = rand() % 2;



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
				CObjMgr::Get_Instance()->Add_Object(OBJ_MUSHROOM, CAbstractFactory<CMushroom>::Create(m_tInfo.fX, m_tInfo.fY, true));
				m_bCheck = true;
				break;
			case 1:
				CObjMgr::Get_Instance()->Add_Object(OBJ_COIN, CAbstractFactory<CTimeitem>::Create(m_tInfo.fX, m_tInfo.fY, true));
				m_bCheck = true;
				break;
			}
			break;
		}

	}













	


	
}