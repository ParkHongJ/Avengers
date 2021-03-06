#include "stdafx.h"
#include "Coin.h"
#include "ScrollMgr.h"   //스크롤 매니저 헤더 추가
CCoin::CCoin()
{
}

CCoin::~CCoin()
{
	Release();
}

void CCoin::Initialize(void)
{


	m_tInfo.fX = 600.f;		// 중점 X
	m_tInfo.fY = 300.f;		// 중점 Y

	m_tInfo.fCX = 32.f;
	m_tInfo.fCY = 32.f;


	
}

int CCoin::Update(void)
{
	if (m_bDead)               // 살았니 죽었니 코드 
		return OBJ_DEAD;

	if (m_tInfo.fY >= m_itembox_y)
	{
		--m_tInfo.fY;
	}
	
	//코인의 중점좌표가 도달지점보다 커질때까지 코인의 중점좌표를 감소시킨다.

	
	Update_Rect();
	return 0;
}

void CCoin::Late_Update(void)
{
}

void CCoin::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();

	HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(255, 215, 0));
	HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);

	Ellipse(hDC, m_tRect.left + iScrollX + 12, m_tRect.top + 10, m_tRect.right + iScrollX - 12, m_tRect.bottom - 10);

	SelectObject(hDC, oldBrush);
	DeleteObject(myBrush);

	TCHAR lpOut[1024];
	SetBkMode(hDC, 1);

	wsprintf(lpOut, TEXT("$"));
	TextOut(hDC, m_tRect.left + iScrollX + 20, m_tRect.top + 16, lpOut, lstrlen(lpOut));
}
void CCoin::Release(void)
{

}



void CCoin::OnCollision(CObj* other)
{
	Set_Dead();
	CGameMgr::Get_Instance()->PlusScore();
}
