#include "stdafx.h"
#include "Mushroom.h"
#include "Player.h"
#include "ScrollMgr.h"
#include "resource.h"

CMushroom::CMushroom()
{
}

CMushroom::~CMushroom()
{
	Release();
}

void CMushroom::Initialize(void)
{
	m_tInfo.fCX = 32.f;
	m_tInfo.fCY = 32.f;

	m_Tag = "Mushroom";                         //태그 추가 
	m_Sprite = IDB_MUSHROOM;
}

int CMushroom::Update(void)
{
	if (m_bDead)               // 살았니 죽었니 코드 
		return OBJ_DEAD;

	if (m_tInfo.fY >= m_itembox_y)
	{
		--m_tInfo.fY;
	}
	Update_Rect();

	return 0;
}

void CMushroom::Late_Update(void)
{
}

void CMushroom::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	HDC MemDC;
	HBITMAP MyBitmap, OldBitmap;
	m_tRect.right += iScrollX - 5;
	m_tRect.left += iScrollX + 5;
	MemDC = CreateCompatibleDC(hDC);

	MyBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(m_Sprite));
	OldBitmap = (HBITMAP)SelectObject(MemDC, MyBitmap);
	TransparentBlt(hDC, m_tRect.left, m_tRect.top, 32, 32, MemDC, 0, 0, 16, 16, RGB(0, 0, 0));
	SelectObject(MemDC, OldBitmap);
	DeleteObject(MyBitmap);
	DeleteDC(MemDC);
}

void CMushroom::Release(void)
{
}

void CMushroom::OnCollision(CObj* other)
{
	Set_Dead();                                      //죽어서
	if (other->CompareTag("Player"))                 //플레이어 크기 커지는 코드
	{
		dynamic_cast<CPlayer*>(other)->UpLife();
	}
}
