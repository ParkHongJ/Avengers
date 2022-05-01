#include "stdafx.h"
#include "Mouse.h"
#include "ScrollMgr.h"

CMouse::CMouse()
{
}

CMouse::~CMouse()
{
	Release();
}

void CMouse::Initialize(void)
{
	m_tInfo.fCX = 10.f;
	m_tInfo.fCY = 10.f;
}

int CMouse::Update(void)
{
	POINT	pt{};

	GetCursorPos(&pt);	// 현재 마우스의 위치 좌표를 얻어오는 함수
	ScreenToClient(g_hWnd, &pt);	// 전체 스크린영역에서 생성한 클라이언트(창) 좌표로 변환

	int iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	m_tInfo.fX = (float)pt.x - iScrollX;
	m_tInfo.fY = (float)pt.y;
	
	Update_Rect();
	ShowCursor(false);		// 마우스 커서를 출력하지 않겠다.

	return OBJ_NOEVENT;
}

void CMouse::Late_Update(void)
{
	

}

void CMouse::Render(HDC hDC)
{
	int iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	Ellipse(hDC, m_tRect.left + iScrollX, m_tRect.top, m_tRect.right + iScrollX, m_tRect.bottom);
}

void CMouse::Release(void)
{
	
}

void CMouse::OnCollision(DIRECTION eDir, CObj* other)
{
	if (other->CompareTag("Block"))
		m_pTarget = other;
}
