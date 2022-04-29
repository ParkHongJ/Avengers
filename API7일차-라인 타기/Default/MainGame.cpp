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

	// main�� �ִ� hWnd ID ���� ���´�
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
	//������۸� ��ó : https://blog.naver.com/PostView.nhn?isHttpsRedirect=true&blogId=kyed203&logNo=20187732037&beginTime=0&jumpingVid=&from=section&redirect=Log&widgetTypeCall=true
/** ������۸� ����ó���Դϴ�. **/
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

	// TODO: ���⿡ �׸��� �ڵ带 �߰��մϴ�.

	// ū �׸� �׷��� ���� ������ �׸��� �����ش�.
	Rectangle(m_hDC, 0, 0, WINCX, WINCY);

	CObjMgr::Get_Instance()->Render(m_hDC);

	// FPS ���
	++m_iFPS;

	if (m_dwTime + 1000 < GetTickCount())
	{
		swprintf_s(m_szFPS, L"FPS : %d", m_iFPS);
		SetWindowText(g_hWnd, m_szFPS);

		m_iFPS = 0;
		m_dwTime = GetTickCount();
	}


	/** ������۸� ��ó�� �Դϴ�. **/
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