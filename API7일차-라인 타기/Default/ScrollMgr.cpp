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
	m_fScrollX = 0.f;
}

void CScrollMgr::Update()
{
	if (!m_pTarget)
		return;

	m_fScrollX = - m_pTarget->Get_Info().fX + 400.f;

	if (MAPSIZE_LEFT + 400.f >= m_pTarget->Get_Info().fX)
		m_fScrollX = 0.f;
	else if (1200.f - 400.f <= m_pTarget->Get_Info().fX)
		m_fScrollX = -MAPSIZE_RIGHT + 800.f;
}

