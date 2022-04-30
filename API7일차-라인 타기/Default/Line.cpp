#include "stdafx.h"
#include "Line.h"
#include "ScrollMgr.h"

CLine::CLine()
	: m_tInfo()
{
	m_tInfo.m_tXInfo.tLPoint.fX = 200.f;
	m_tInfo.m_tXInfo.tLPoint.fY = 100.f;
	m_tInfo.m_tXInfo.tRPoint.fX = 300.f;
	m_tInfo.m_tXInfo.tRPoint.fY = 100.f;

	//Y축 위쪽 점을 L포인트라고 해놨음
	m_tInfo.m_tYInfo.tLPoint.fX = 250.f;


}


CLine::CLine(LINEPOINT& tLeft, LINEPOINT& tRight)
	//: m_tInfo(tLeft, tRight)
{

}

CLine::CLine(LINE tLine)
	//: m_tInfo(tLine)
{

}

CLine::~CLine()
{
}

void CLine::Render(HDC hDC)
{
	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	/*MoveToEx(hDC, (int)m_tInfo.tLPoint.fX + iScrollX, (int)m_tInfo.tLPoint.fY, nullptr);
	LineTo(hDC, (int)m_tInfo.tRPoint.fX + iScrollX, (int)m_tInfo.tRPoint.fY);*/
}

