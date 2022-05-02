#include "stdafx.h"
#include "UIMgr.h"
#include "GameMgr.h"

CUIMgr* CUIMgr::m_pInstance = nullptr;

CUIMgr::CUIMgr()
{
}

CUIMgr::~CUIMgr()
{
	Release();
}

void CUIMgr::Initialize()
{
	m_iScore = 0;
	m_iLifeCount = 1;

	m_pScorePos.x = 400.f;
	m_pScorePos.y = 0.f;
	m_pLifeCountPos.x = 0.f;
	m_pLifeCountPos.y = 0.f;
	iR = 0;
	iG = 0;
	iB = 0;

	m_pEditTopDown.x = 200.f;
	m_pEditTopDown.y = 530.f;

	m_pStartTopDown.x = 320.f;
	m_pStartTopDown.y = 300.f;
}

void CUIMgr::Update(void)
{

}

void CUIMgr::Render(HDC hDC)
{
	// CoinRender(hDC);
	// LifeCountRender(hDC);
	// MapEditorRender(hDC);
}

void CUIMgr::CoinRender(HDC hDC)
{
	HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(255, 215, 0));
	HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);

	Ellipse(hDC, 10 + m_pScorePos.x, 10 + m_pScorePos.y, 30 + m_pScorePos.x, 35 + m_pScorePos.y);

	SelectObject(hDC, oldBrush);
	DeleteObject(myBrush);

	TCHAR lpOut[1024];
	SetBkMode(hDC, 1);

	wsprintf(lpOut, TEXT("$"));
	TextOut(hDC, m_pScorePos.x + 16, m_pScorePos.y + 14, lpOut, lstrlen(lpOut));

	wsprintf(lpOut, TEXT("x %d"), m_iScore);
	TextOut(hDC, 35 + m_pScorePos.x, 15 + m_pScorePos.y, lpOut, lstrlen(lpOut));
}

void CUIMgr::LifeCountRender(HDC hDC)
{
	float fIntv = 0.f;
	for (int i = 0; i < m_iLifeCount; ++i)
	{
		HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(255, 0, 0));
		HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);

		Ellipse(hDC, 10 + m_pLifeCountPos.x + fIntv, 10 + m_pLifeCountPos.y, 30 + m_pLifeCountPos.x + fIntv, 35 + m_pLifeCountPos.y);

		SelectObject(hDC, oldBrush);
		DeleteObject(myBrush);

		TCHAR lpOut[1024];
		SetBkMode(hDC, 1);
		wsprintf(lpOut, TEXT("L"));
		TextOut(hDC, 10 + m_pLifeCountPos.x + fIntv + 5, 10 + m_pLifeCountPos.y + 5, lpOut, lstrlen(lpOut));

		fIntv += 25.f;
	}
}

void CUIMgr::MapEditorRender(HDC hDC, BLOCKID eID)
{
	int iFrameSize = BLOCK_SIZE + 20;
	int iInterval = iFrameSize + 2;
	int temp = 0;
	for (int i = 0; i < BLOCKID::BLK_END; ++i)
	{
		if (eID == i)
		{
			HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(0, 255, 0));
			HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);

			Rectangle(hDC, m_pEditTopDown.x + temp, m_pEditTopDown.y, m_pEditTopDown.x + iFrameSize + temp, m_pEditTopDown.y + iFrameSize);

			SelectObject(hDC, oldBrush);
			DeleteObject(myBrush);
		}
		else
		{
			Rectangle(hDC, m_pEditTopDown.x + temp, m_pEditTopDown.y, m_pEditTopDown.x + iFrameSize + temp, m_pEditTopDown.y + iFrameSize);
		}

		DrawBlockUI(hDC, m_pEditTopDown.x + temp, m_pEditTopDown.y, m_pEditTopDown.x + iFrameSize + temp, m_pEditTopDown.y + iFrameSize, i);

		TCHAR lpOut[1024];
		wsprintf(lpOut, TEXT("%d"), i + 1);
		TextOut(hDC, m_pEditTopDown.x + temp + 5, m_pEditTopDown.y + 5, lpOut, lstrlen(lpOut));

		temp += iInterval;
	}
}

void CUIMgr::DrawBlockUI(HDC hDC, float left, float top, float right, float bottom, int iID)
{
	BLOCKID eID = (BLOCKID)iID;

	int iterval = 10;
	switch (eID)
	{
	case BLK_BLOCK:
		Rectangle(hDC, left + iterval, top + iterval, right - iterval, bottom - iterval);
		break;
	case BLK_MOVINGBLOCK:
		Rectangle(hDC, left + iterval, top + iterval + 5, right - iterval, bottom - iterval - 5);
		break;
	case BLK_MOVINGBLOCKLR:
		Rectangle(hDC, left + iterval, top + iterval + 5, right - iterval, bottom - iterval - 5);
		break;
	case BLK_RANDOMBOX:
		Rectangle(hDC, left + iterval, top + iterval + 5, right - iterval, bottom - iterval);
		TCHAR lpOut[1024];
		wsprintf(lpOut, TEXT("?"));
		TextOut(hDC, left + iterval + 10, top + iterval + 10, lpOut, lstrlen(lpOut));
		break;
	case BLK_GUMBA:
		Ellipse(hDC, left + iterval, top + iterval, right - iterval, bottom - iterval);
		break;
	case BLK_TURTLE:
		Ellipse(hDC, left + iterval, top + iterval+5, right - iterval, bottom - iterval-5);
		break;
	case BLK_KOOPA:
		Rectangle(hDC, left + iterval, top + iterval, right - iterval, bottom - iterval);
		break;
	case BLK_COIN:
	{
		HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(255, 215, 0));
		HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);

		Ellipse(hDC, left+12, top+10, right-12, bottom-10);

		SelectObject(hDC, oldBrush);
		DeleteObject(myBrush);

		TCHAR lpOut[1024];
		SetBkMode(hDC, 1);

		wsprintf(lpOut, TEXT("$"));
		TextOut(hDC, left + 20, top + 16, lpOut, lstrlen(lpOut));
	}
		break;
	case BLK_END:
		break;
	}
}

void CUIMgr::StartSceneRender(HDC hDC, SCENEID eID)
{
	int iFrameSize = BLOCK_SIZE + 40;
	int iInterval = iFrameSize + 10;
	int temp = 0;

	for (int i = 1; i <= SCENEID::SCENE_END; ++i)
	{
		if (eID == i)
		{
			HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(0, 255, 0));
			HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);

			Rectangle(hDC, m_pStartTopDown.x, m_pStartTopDown.y + temp, m_pStartTopDown.x + iFrameSize + 100, m_pStartTopDown.y + iFrameSize + temp);

			SelectObject(hDC, oldBrush);
			DeleteObject(myBrush);
		}
		else
		{
			Rectangle(hDC, m_pStartTopDown.x, m_pStartTopDown.y + temp, m_pStartTopDown.x + iFrameSize + 100, m_pStartTopDown.y + iFrameSize + temp);
		}

		temp += iInterval;
	}

	TCHAR lpOut[1024];
	SetBkMode(hDC, 1);

	wsprintf(lpOut, TEXT("START"));
	TextOut(hDC, m_pStartTopDown.x + 5 + 60, m_pStartTopDown.y + (iFrameSize + 10)*0 + 5 + 20, lpOut, lstrlen(lpOut));

	wsprintf(lpOut, TEXT("EDIT MAP"));
	TextOut(hDC, m_pStartTopDown.x + 5 + 50, m_pStartTopDown.y + (iFrameSize + 10)*1 + 5 + 20, lpOut, lstrlen(lpOut));

	wsprintf(lpOut, TEXT("EXIT"));
	TextOut(hDC, m_pStartTopDown.x + 5 + 65, m_pStartTopDown.y + (iFrameSize + 10)*2 + 5 + 20, lpOut, lstrlen(lpOut));

}

void CUIMgr::StartSceneBackGround(HDC hDC)
{
	++iR;
	if (255 <= iR)
	{
		iR = 255;
		++iG;
		if (255 <= iG)
		{
			iG = 255;
			++iB;
			if (255 <= iB)
			{
				iR = 0;
				iG = 0;
				iB = 0;
			}
		}
	}

	HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(iR, iG, iB));
	HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);

	Rectangle(hDC, 0, 0, 800, 600);

	SelectObject(hDC, oldBrush);
	DeleteObject(myBrush);
}

void CUIMgr::GameSceneBackGround(HDC hDC)
{
	HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(80, 188, 223));
	HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);

	Rectangle(hDC, MAPSIZE_LEFT, 0, MAPSIZE_RIGHT, 600);

	SelectObject(hDC, oldBrush);
	DeleteObject(myBrush);
}

void CUIMgr::Release()
{
	m_iScore = 0;
	m_iLifeCount = 0;
}