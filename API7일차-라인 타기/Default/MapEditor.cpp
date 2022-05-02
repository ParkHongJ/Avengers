#include "stdafx.h"
#include "MapEditor.h"

#include "AbstractFactory.h"

#include "ScrollMgr.h"
#include "KeyMgr.h"
#include "ObjMgr.h"
#include "UIMgr.h"

#include "Mouse.h"
#include "Block.h"
#include "MovingBlock.h"
#include "MovingBlockLR.h"

CMapEditor* CMapEditor::m_pInstance = nullptr;

CMapEditor::CMapEditor()
{
}

CMapEditor::~CMapEditor()
{
	Release();
}

void CMapEditor::Initialize()
{
	CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CMouse>::Create());

	m_sMousePos.x = 0.f;
	m_sMousePos.y = 0.f;
	m_eCurBlockID = BLOCKID::BLK_BLOCK;

	ShowCursor(false);
}

void CMapEditor::Update(void)
{
	POINT	pt{};

	// 화면상 마우스 좌표
	GetCursorPos(&pt);				
	ScreenToClient(g_hWnd, &pt);	

	// 게임상 마우스 좌표
	int iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	m_sMousePos.x = (float)pt.x - iScrollX;
	m_sMousePos.y = (float)pt.y;

	// 현재 블럭 위치
	int iIdx_X = m_sMousePos.x / BLOCK_SIZE;
	int iIdx_Y = m_sMousePos.y / BLOCK_SIZE;
	m_sCurBlockPos.x = BLOCK_SIZE * iIdx_X + 16;
	m_sCurBlockPos.y = BLOCK_SIZE * iIdx_Y + 16;

	Update_GetKey();
}

void CMapEditor::Render(HDC hDC)
{
	TCHAR lpOut[1024];
	wsprintf(lpOut, TEXT("lX: %d \nY: %d"), m_sMousePos.x, m_sMousePos.y);
	TextOut(hDC, 35, 15, lpOut, lstrlen(lpOut));

	int iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();

	Rectangle(hDC, m_sCurBlockPos.x - 16 + iScrollX, m_sCurBlockPos.y - 16, m_sCurBlockPos.x + BLOCK_SIZE - 16 + iScrollX, m_sCurBlockPos.y + BLOCK_SIZE - 16);

	CUIMgr::Get_Instance()->MapEditorRender(hDC, m_eCurBlockID);
}

void CMapEditor::Release()
{
	m_BlockList.clear();
}


void CMapEditor::Update_GetKey()
{
	// 좌우 화면 이동
	if (CKeyMgr::Get_Instance()->Key_Pressing('A'))
		CScrollMgr::Get_Instance()->Set_ScrollX(5.f);
	if (CKeyMgr::Get_Instance()->Key_Pressing('D'))
		CScrollMgr::Get_Instance()->Set_ScrollX(-5.f);

	// 블럭 선택 1~9
	for (int i = 1; i <= BLOCKID::BLK_END; ++i)
	{
		char temp = 48 + i;
		if (57 < temp) continue;
		if (CKeyMgr::Get_Instance()->Key_Down(temp))
			m_eCurBlockID = (BLOCKID)(i - 1);
	}

	// 블럭 설치
	if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE))
		Edit_CreateBlock();
	// 블럭 삭제
	if (CKeyMgr::Get_Instance()->Key_Down('X'))
		Edit_DeleteBlock();

	if (CKeyMgr::Get_Instance()->Key_Down('O'))
		Save();
	if (CKeyMgr::Get_Instance()->Key_Down('P'))
		Load();
}

void CMapEditor::Edit_CreateBlock()
{
	m_BlockList.push_back(BlockInfo{(float)m_sCurBlockPos.x, (float)m_sCurBlockPos.y, m_eCurBlockID});
	CreateBlock(m_eCurBlockID, m_sCurBlockPos.x, m_sCurBlockPos.y);
}

void CMapEditor::CreateBlock(BLOCKID eId, float fX, float fY)
{
	switch (eId)
	{
	case BLOCKID::BLK_BLOCK:
		CObjMgr::Get_Instance()->Add_Object(OBJ_BLOCK, CAbstractFactory<CBlock>::Create(fX, fY, 0.f));
		break;
	case BLOCKID::BLK_MOVINGBLOCK:
		CObjMgr::Get_Instance()->Add_Object(OBJ_MOVINGBLOCK, CAbstractFactory<CMovingBlockLR>::Create(fX, fY, 0.f));
		break;
	}
}

void CMapEditor::Edit_DeleteBlock()
{
	CObj* targetBlock = CObjMgr::Get_Instance()->Get_Mouse()->Get_Target();
	if (!targetBlock)
		return;

	targetBlock->Set_Dead();
	for (list<BlockInfo>::iterator iter = m_BlockList.begin(); iter != m_BlockList.end();)
	{
		if (targetBlock->Get_Dead())
			iter = m_BlockList.erase(iter);
		else
			++iter;
	}
}


void CMapEditor::Save()
{
	// 1. 파일 개방

// CreateFile : api 파일 개방 함수, 개방 실패 시 INVALID_HANDLE_VALUE하기 때문에 null값으로 예외처리를 할 수 없다.

	HANDLE		hFile = CreateFile(L"../Data/MapData.dat",			// 파일 경로와 이름 명시
		GENERIC_WRITE,				// 파일 접근 모드 (GENERIC_WRITE 쓰기 전용, GENERIC_READ 읽기 전용)
		NULL,						// 공유방식, 파일이 열려있는 상태에서 다른 프로세스가 오픈할 때 허용할 것인가, NULL인 경우 공유하지 않는다
		NULL,						// 보안 속성, 기본값	
		CREATE_ALWAYS,				// 생성 방식, CREATE_ALWAYS는 파일이 없다면 생성, 있다면 덮어 쓰기, OPEN_EXISTING 파일이 있을 경우에면 열기
		FILE_ATTRIBUTE_NORMAL,		// 파일 속성(읽기 전용, 숨기 등), FILE_ATTRIBUTE_NORMAL 아무런 속성이 없는 일반 파일 생성
		NULL);						// 생성도리 파일의 속성을 제공할 템플릿 파일, 우리는 사용하지 않아서 NULL

	if (INVALID_HANDLE_VALUE == hFile)
	{
		// 팝업 창을 출력해주는 기능의 함수
		// 1. 핸들 2. 팝업 창에 띄우고자하는 메시지 3. 팝업 창 이름 4. 버튼 속성
		MessageBox(g_hWnd, _T("Save File"), _T("Fail"), MB_OK);
		return;
	}

	// 2. 파일 쓰기

	DWORD		dwByte = 0;

	for (auto& iter : m_BlockList)
	{
		WriteFile(hFile, &iter, sizeof(BlockInfo), &dwByte, nullptr);
	}


	// 3. 파일 소멸
	CloseHandle(hFile);

	MessageBox(g_hWnd, _T("Save 완료"), _T("성공"), MB_OK);
}

void CMapEditor::Load()
{
	HANDLE		hFile = CreateFile(L"../Data/MapData.dat",			// 파일 경로와 이름 명시
		GENERIC_READ,				// 파일 접근 모드 (GENERIC_WRITE 쓰기 전용, GENERIC_READ 읽기 전용)
		NULL,						// 공유방식, 파일이 열려있는 상태에서 다른 프로세스가 오픈할 때 허용할 것인가, NULL인 경우 공유하지 않는다
		NULL,						// 보안 속성, 기본값	
		OPEN_EXISTING,				// 생성 방식, CREATE_ALWAYS는 파일이 없다면 생성, 있다면 덮어 쓰기, OPEN_EXISTING 파일이 있을 경우에면 열기
		FILE_ATTRIBUTE_NORMAL,		// 파일 속성(읽기 전용, 숨기 등), FILE_ATTRIBUTE_NORMAL 아무런 속성이 없는 일반 파일 생성
		NULL);						// 생성도리 파일의 속성을 제공할 템플릿 파일, 우리는 사용하지 않아서 NULL

	if (INVALID_HANDLE_VALUE == hFile)
	{
		// 팝업 창을 출력해주는 기능의 함수
		// 1. 핸들 2. 팝업 창에 띄우고자하는 메시지 3. 팝업 창 이름 4. 버튼 속성
		MessageBox(g_hWnd, _T("Load File"), _T("Fail"), MB_OK);
		return;
	}

	// 2. 파일 쓰기

	DWORD		dwByte = 0;
	BlockInfo		tInfo{};

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(BlockInfo), &dwByte, nullptr);

		if (0 == dwByte)	// 더이상 읽을 데이터가 없을 경우
			break;

		m_BlockList.push_back(BlockInfo{ (float)tInfo.fX, (float)tInfo.fY, tInfo.eID });
	}


	// 3. 파일 소멸
	CloseHandle(hFile);

	CreateAllBlockInList();
	MessageBox(g_hWnd, _T("Load 완료"), _T("성공"), MB_OK);
}

void CMapEditor::CreateAllBlockInList()
{
	for (auto& iter : m_BlockList)
		CreateBlock(iter.eID, iter.fX, iter.fY);
}
