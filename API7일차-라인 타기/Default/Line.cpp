#include "stdafx.h"
#include "Line.h"


CLine::CLine()
	: m_tInfo()
{
}


CLine::CLine(LINEPOINT& tLeft, LINEPOINT& tRight)
	: m_tInfo(tLeft, tRight)
{

}

CLine::~CLine()
{
}

void CLine::Render(HDC hDC)
{
	MoveToEx(hDC, (int)m_tInfo.tLPoint.fX, (int)m_tInfo.tLPoint.fY, nullptr);
	LineTo(hDC, (int)m_tInfo.tRPoint.fX, (int)m_tInfo.tRPoint.fY);
}
