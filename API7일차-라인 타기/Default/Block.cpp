#include "stdafx.h"
#include "Block.h"

#include "SCrollMgr.h"

CBlock::CBlock()
{
}

CBlock::~CBlock()
{
	Release();
}

void CBlock::Initialize(void)
{
	m_tInfo.fX = 600.f;		// 중점 X
	m_tInfo.fY = 300.f;		// 중점 Y

	m_tInfo.fCX = 32.f;
	m_tInfo.fCY = 32.f;

	m_fSpeed = 1.f;

	m_eDir = DIR_LEFT;
	m_tItemInfo.fX = 256.f;
	m_tItemInfo.fY = 300.f;

	m_tItemInfo.fCX = 32.f;
	m_tItemInfo.fCY = 32.f;

	m_Tag = "Block";
}

int CBlock::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	Update_Rect();

	//if(아이템이 활성화 되어있나?) -> 이거는 아이템말고 블럭활성화로 바꾸는게 좋을듯
	if (m_tItemInfo.fY >= m_tInfo.fY - 32.f)
	{
		m_tItemInfo.fY -= m_fItemSpeed;
	}
	//item->Update_ItemRect() 
	m_tItemRect.left = long(m_tItemInfo.fX - (m_tItemInfo.fCX / 2.f));
	m_tItemRect.top = long(m_tItemInfo.fY - (m_tItemInfo.fCY / 2.f));
	m_tItemRect.right = long(m_tItemInfo.fX + (m_tItemInfo.fCX / 2.f));
	m_tItemRect.bottom = long(m_tItemInfo.fY + (m_tItemInfo.fCY / 2.f));

	return OBJ_NOEVENT;
}

void CBlock::Late_Update(void)
{
}

void CBlock::Render(HDC hDC)
{
	//Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	//Ellipse(hDC, m_tItemRect.left, m_tItemRect.top, m_tItemRect.right, m_tItemRect.bottom);

	int iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top, m_tRect.right + iScrollX, m_tRect.bottom);
}

void CBlock::Release(void)
{
}

void CBlock::OnCollision()
{
}

void CBlock::OnCollision(DIRECTION eDir)
{
	switch (eDir)
	{
	case DIR_DOWN:
		m_fItemSpeed = 1.f;
		break;
	}
}
