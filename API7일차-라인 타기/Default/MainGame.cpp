#include "stdafx.h"

#include "MainGame.h"
#include "AbstractFactory.h"
#include "CollisionMgr.h"
#include "Shield.h"
#include "Mouse.h"
#include "ObjMgr.h"

#include "Player.h"
#include "Monster.h"

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

	// main에 있는 hWnd ID 값을 얻어온다
	m_hDC = GetDC(g_hWnd);

	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create());

	for (int i = 0; i < 100; ++i)
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonster>::Create(32 * i, 400.f, 0.f));
		CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonster>::Create(256 + 32 * i, 300.f, 0.f));
	}
}


void CMainGame::Update(void)
{
	CObjMgr::Get_Instance()->Update();
}

void CMainGame::Late_Update(void)
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CMainGame::Render(void)
{
	//더블버퍼링 출처 : https://blog.naver.com/PostView.nhn?isHttpsRedirect=true&blogId=kyed203&logNo=20187732037&beginTime=0&jumpingVid=&from=section&redirect=Log&widgetTypeCall=true
/** 더블버퍼링 시작처리입니다. **/
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

	// TODO: 여기에 그리기 코드를 추가합니다.

	// 큰 네모를 그려서 이전 프레임 그림을 덮어준다.
	Rectangle(m_hDC, 0, 0, WINCX, WINCY);

	CObjMgr::Get_Instance()->Render(m_hDC);

	// FPS 출력
	++m_iFPS;

	if (m_dwTime + 1000 < GetTickCount())
	{
		swprintf_s(m_szFPS, L"FPS : %d", m_iFPS);
		SetWindowText(g_hWnd, m_szFPS);

		m_iFPS = 0;
		m_dwTime = GetTickCount();
	}


	/** 더블버퍼링 끝처리 입니다. **/
	tmpDC = m_hDC;
	m_hDC = MemDC;
	MemDC = tmpDC;
	GetClientRect(g_hWnd, &bufferRT);
	BitBlt(m_hDC, 0, 0, bufferRT.right, bufferRT.bottom, MemDC, 0, 0, SRCCOPY);
	SelectObject(MemDC, oldBackBit);
	DeleteObject(BackBit);
	DeleteDC(MemDC);

}

void CMainGame::Release(void)
{
	CObjMgr::Get_Instance()->Destroy_Instance();

	ReleaseDC(g_hWnd, m_hDC);
}