#include "stdafx.h"

#include "MainGame.h"
#include "AbstractFactory.h"
#include "CollisionMgr.h"
#include "Shield.h"
#include "Mouse.h"
#include "ObjMgr.h"
#include "LineMgr.h"
#include "CBox.h"
#include "Player.h"
#include "Monster.h"
#include "Block.h"
#include "MovingBlock.h"
#include "ScrollMgr.h"
#include "Gumba.h"
#include "Turtle.h"
#include "Coin.h"
#include "UIMgr.h"
#include "MapEditor.h"

float CMainGame::m_fTime = 1.f;
#include "Coin.h"
#include "CKoopa.h"

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

	CMapEditor::Get_Instance()->Initialize();
	// CMapEditor::Get_Instance()->Load();

	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create());
	CScrollMgr::Get_Instance()->Set_Target(CObjMgr::Get_Instance()->Get_Player());
	CScrollMgr::Get_Instance()->Initialize();
	CUIMgr::Get_Instance()->Initialize();

	//CObjMgr::Get_Instance()->Add_Object(OBJ_BLOCK, CAbstractFactory<CMovingBlock>::Create(70.f, 250.f, 0.f));
	//CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CCoin>::Create(rand()%500+300, rand()%300+100, 0.f));	
  
  CObjMgr::Get_Instance()->Add_Object(OBJ_TEMP, CAbstractFactory<CGumba>::Create(400.f, 350.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_TEMP, CAbstractFactory<CTurtle>::Create(300.f, 350.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_TEMP, CAbstractFactory<CKoopa>::Create(400.f, 0.f));

}


void CMainGame::Update(void)
{
	CObjMgr::Get_Instance()->Update();
	CScrollMgr::Get_Instance()->Update();
	CMapEditor::Get_Instance()->Update();
}

void CMainGame::Late_Update(void)
{
	CObjMgr::Get_Instance()->Late_Update();
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

	CObjMgr::Get_Instance()->Render(m_hDC);
	CMapEditor::Get_Instance()->Render(m_hDC);

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
	CObjMgr::Get_Instance()->Destroy_Instance();
	CScrollMgr::Get_Instance()->Destroy_Instance();
	CUIMgr::Get_Instance()->Destroy_Instance();
	CMapEditor::Get_Instance()->Destroy_Instance();

	ReleaseDC(g_hWnd, m_hDC);
}