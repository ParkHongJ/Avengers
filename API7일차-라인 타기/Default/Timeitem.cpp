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
	if (m_bDead)               // 살았니 죽었니 코드 
		return OBJ_DEAD;

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
	Set_Dead();                                //죽었을떄 GameManager의 시간을 군바의 시간을 바꿔요 
	CGameMgr::Get_Instance()->Set_Time(0.1);

}
