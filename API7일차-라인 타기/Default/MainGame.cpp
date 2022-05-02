#include "stdafx.h"
#include "MainGame.h"
#include "AbstractFactory.h"

#include "SceneMgr.h"
#include "KeyMgr.h"
#include "MapEditor.h"
#include "ObjMgr.h"
#include "SceneMgr.h"
#include "ScrollMgr.h"
#include "UIMgr.h"


float CMainGame::m_fTime = 1.f;

#include "Coin.h"
#include "Mushroom.h"
#include "GameMgr.h" // GameMgr 헤더추가 
#include "Timeitem.h"


CMainGame::CMainGame()
	: m_hDC(nullptr)
	, m_dwTime(GetTickCount())
{
	ZeroMemory(m_szFPS, sizeof(TCHAR) * 64);
	m_iFPS = 0;
}

CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize(void)
{
	m_hDC = GetDC(g_hWnd);

	CSceneMgr::Get_Instance()->Initailize();
}

void CMainGame::Update(void)
{
	CSceneMgr::Get_Instance()->Update();
}

void CMainGame::Late_Update(void)
{
	CSceneMgr::Get_Instance()->Late_Update();
}

void CMainGame::Render(void)
{
#pragma region 더블 버퍼링 시작
	//출처 : https://blog.naver.com/PostView.nhn?isHttpsRedirect=true&blogId=kyed203&logNo=20187732037&beginTime=0&jumpingVid=&from=section&redirect=Log&widgetTypeCall=true
	HDC MemDC, tmpDC;
	HBITMAP BackBit, oldBackBit;
	RECT bufferRT;

	GetClientRect(g_hWnd, &bufferRT);
	MemDC = CreateCompatibleDC(m_hDC);
	BackBit = CreateCompatibleBitmap(m_hDC, bufferRT.right, bufferRT.bottom);
	oldBackBit = (HBITMAP)SelectObject(MemDC, BackBit);
	PatBlt(MemDC, 0, 0, bufferRT.right, bufferRT.bottom, WHITENESS);
	tmpDC = m_hDC;
	m_hDC = MemDC;
	MemDC = tmpDC;
#pragma endregion

	// =========Render============

	CSceneMgr::Get_Instance()->Render(m_hDC);

	// ===========================

#pragma region 더블 버퍼링 끝
	tmpDC = m_hDC;
	m_hDC = MemDC;
	MemDC = tmpDC;
	GetClientRect(g_hWnd, &bufferRT);
	BitBlt(m_hDC, 0, 0, bufferRT.right, bufferRT.bottom, MemDC, 0, 0, SRCCOPY);
	SelectObject(MemDC, oldBackBit);
	DeleteObject(BackBit);
#pragma endregion

#pragma region FPS
	++m_iFPS;

	if (m_dwTime + 1000 < GetTickCount())
	{
		swprintf_s(m_szFPS, L"FPS : %d", m_iFPS);
		SetWindowText(g_hWnd, m_szFPS);

		m_iFPS = 0;
		m_dwTime = GetTickCount();
	}
#pragma endregion

}

void CMainGame::Release(void)
{
	CSceneMgr::		Get_Instance()->Destroy_Instance();
	CObjMgr::		Get_Instance()->Destroy_Instance();
	CScrollMgr::	Get_Instance()->Destroy_Instance();
	CUIMgr::		Get_Instance()->Destroy_Instance();
	CMapEditor::	Get_Instance()->Destroy_Instance();
	CKeyMgr::		Get_Instance()->Destroy_Instance();
	
  // Gamemanager 싱글톤 파괴추가
	ReleaseDC(g_hWnd, m_hDC);
}

