#include "stdafx.h"
#include "ScrollMgr.h"

CScrollMgr* CScrollMgr::m_pInstance = nullptr;

CScrollMgr::CScrollMgr()
	:m_pTarget(nullptr)
{
}

CScrollMgr::~CScrollMgr()
{
}

void CScrollMgr::Initialize(void)
{
}

void CScrollMgr::Update()
{
	if (!m_pTarget)
		return;

	m_fScrollX = -m_pTarget->Get_Info().fX + 400.f;

	// Fixe Wall
	//if (MAPSIZE_LEFT >= -m_fScrollX)
	//	m_fScrollX = 0.f;
	//if (MAPSIZE_RIGHT <= -m_fScrollX)
	//	m_fScrollX = -1600.f;

	if (MAPSIZE_LEFT + 400.f >= m_pTarget->Get_Info().fX)
		m_fScrollX = 0.f;
	else if (MAPSIZE_RIGHT - 400.f <= m_pTarget->Get_Info().fX)
		m_fScrollX = -MAPSIZE_RIGHT + 800.f;
}

