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

	GetCursorPos(&pt);	// ���� ���콺�� ��ġ ��ǥ�� ������ �Լ�
	ScreenToClient(g_hWnd, &pt);	// ��ü ��ũ���������� ������ Ŭ���̾�Ʈ(â) ��ǥ�� ��ȯ

	int iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	m_tInfo.fX = (float)pt.x - iScrollX;
	m_tInfo.fY = (float)pt.y;
	
	Update_Rect();
	ShowCursor(false);		// ���콺 Ŀ���� ������� �ʰڴ�.

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
