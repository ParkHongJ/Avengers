#include "stdafx.h"
#include "UIMgr.h"

CUIMgr* CUIMgr::m_pInstance = nullptr;

CUIMgr::CUIMgr()
{
}

CUIMgr::~CUIMgr()
{
}

void CUIMgr::Initialize()
{
	m_iScore = 0;
	m_iLifeCount = 0;

	m_pScorePos.x = 400.f;
	m_pScorePos.y = 0.f;
	m_pLifeCountPos.x = 0.f;
	m_pLifeCountPos.y = 0.f;
}

void CUIMgr::Update(void)
{

}

void CUIMgr::Render(HDC hDC)
{
	CoinRender(hDC);
	LifeCountRender(hDC);
}

void CUIMgr::CoinRender(HDC hDC)
{
	Ellipse(hDC, 10 + m_pScorePos.x, 10 + m_pScorePos.y, 30 + m_pScorePos.x, 35 + m_pScorePos.y);

	TCHAR lpOut[1024];
	wsprintf(lpOut, TEXT("x %d"), m_iScore);
	TextOut(hDC, 35 + m_pScorePos.x, 15 + m_pScorePos.y, lpOut, lstrlen(lpOut));
}

void CUIMgr::LifeCountRender(HDC hDC)
{
	float fIntv = 0.f;
	for (int i = 0; i < m_iLifeCount; ++i)
	{
		Rectangle(hDC, 10 + m_pLifeCountPos.x + fIntv, 10 + m_pLifeCountPos.y, 30 + m_pLifeCountPos.x + fIntv, 35 + m_pLifeCountPos.y);
		fIntv += 25.f;
	}
}

