#include "stdafx.h"
#include "LineMgr.h"

CLineMgr*		CLineMgr::m_pInstance = nullptr;

CLineMgr::CLineMgr()
{
}


CLineMgr::~CLineMgr()
{
	Release();
}

void CLineMgr::Initialize(void)
{
	LINEPOINT	tLine[4] {
		{ 100.f, 450.f },
		{ 300.f, 450.f },
		{ 500.f, 250.f },
		{ 700.f, 250.f }
	};

	m_LineList.push_back(new CLine(tLine[0], tLine[1]));
	m_LineList.push_back(new CLine(tLine[1], tLine[2]));
	m_LineList.push_back(new CLine(tLine[2], tLine[3]));
}

void CLineMgr::Render(HDC hDC)
{
	for (auto& iter : m_LineList)
		iter->Render(hDC);
}

void CLineMgr::Release(void)
{
	for_each(m_LineList.begin(), m_LineList.end(), CDeleteObj());
	m_LineList.clear();
}

bool CLineMgr::Collision_Line(float& _fX, float* pY)
{
	// 직선의 방정식

	// Y - y1 = ((y2 - y1) / (x2 - x1)) * X - x1
	// Y  = (((y2 - y1) / (x2 - x1)) * (X - x1)) + y1

	if (m_LineList.empty())
		return false;

	CLine*		pTarget = nullptr;

	for (auto& iter : m_LineList)
	{
		if (_fX >= iter->Get_Info().tLPoint.fX &&
			_fX <= iter->Get_Info().tRPoint.fX)
		{
			pTarget = iter;
		}
	}

	if (!pTarget)
		return false;

	float	x1 = pTarget->Get_Info().tLPoint.fX;
	float	x2 = pTarget->Get_Info().tRPoint.fX;

	float	y1 = pTarget->Get_Info().tLPoint.fY;
	float	y2 = pTarget->Get_Info().tRPoint.fY;

	*pY = (((y2 - y1) / (x2 - x1)) * (_fX - x1)) + y1;
		return true;
}
