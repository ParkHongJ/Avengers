#include "stdafx.h"
#include "Timeitem.h"
#include "GameMgr.h"
#include "ScrollMgr.h"
#include "resource.h"
CTimeitem::CTimeitem()
{
}

CTimeitem::~CTimeitem()
{
	Release();
}

void CTimeitem::Initialize(void)
{
	m_tInfo.fCX = 32.f;
	m_tInfo.fCY = 32.f;
	m_Sprite = IDB_TIMEITEM;
}

int CTimeitem::Update(void)
{
	if (m_bDead)               // ��Ҵ� �׾��� �ڵ� 
		return OBJ_DEAD;

	if (m_tInfo.fY >= m_itembox_y)
	{
		--m_tInfo.fY;
	}

	Update_Rect();
	return 0;
}

void CTimeitem::Late_Update(void)
{
}

void CTimeitem::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
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

void CTimeitem::Release(void)
{
}

void CTimeitem::OnCollision(CObj* other)
{
	Set_Dead();                                //�׾����� GameManager�� �ð��� ������ �ð��� �ٲ�� 
	CGameMgr::Get_Instance()->Set_Time(0.1);

}
