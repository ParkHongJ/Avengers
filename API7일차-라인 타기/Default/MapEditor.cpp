#include "stdafx.h"
#include "MapEditor.h"

#include "AbstractFactory.h"

#include "ScrollMgr.h"
#include "KeyMgr.h"
#include "ObjMgr.h"
#include "UIMgr.h"
#include "SceneMgr.h"

#include "Mouse.h"
#include "Block.h"
#include "MovingBlock.h"
#include "MovingBlockLR.h"
#include "CKoopa.h"
#include "Turtle.h"
#include "Gumba.h"
#include "Coin.h"
#include "Randbox.h"


#include "Randbox.h"
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

	// ȭ��� ���콺 ��ǥ
	GetCursorPos(&pt);				
	ScreenToClient(g_hWnd, &pt);	

	// ���ӻ� ���콺 ��ǥ
	int iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	m_sMousePos.x = (float)pt.x - iScrollX;
	m_sMousePos.y = (float)pt.y;

	// ���� ���� ��ġ
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
	// �¿� ȭ�� �̵�
	if (CKeyMgr::Get_Instance()->Key_Pressing('A'))
		CScrollMgr::Get_Instance()->Set_ScrollX(10.f);
	if (CKeyMgr::Get_Instance()->Key_Pressing('D'))
		CScrollMgr::Get_Instance()->Set_ScrollX(-10.f);

	// ���� ���� 1~9
	for (int i = 1; i <= BLOCKID::BLK_END; ++i)
	{
		char temp = 48 + i;
		if (57 < temp) continue;
		if (CKeyMgr::Get_Instance()->Key_Down(temp))
			m_eCurBlockID = (BLOCKID)(i - 1);
	}

	// ���� ��ġ
	if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE))
		Edit_CreateBlock();
	// ���� ����
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
	case BLK_BLOCK:
		CObjMgr::Get_Instance()->Add_Object(OBJ_BLOCK, CAbstractFactory<CBlock>::Create(fX, fY, 0.f));
		break;
	case BLK_MOVINGBLOCK:
		CObjMgr::Get_Instance()->Add_Object(OBJ_MOVINGBLOCK, CAbstractFactory<CMovingBlock>::Create(fX, fY, 0.f));
		break;
	case BLK_MOVINGBLOCKLR:
		CObjMgr::Get_Instance()->Add_Object(OBJ_MOVINGBLOCK, CAbstractFactory<CMovingBlockLR>::Create(fX, fY, 0.f));
		break;
	case BLK_RANDOMBOX:
		CObjMgr::Get_Instance()->Add_Object(OBJ_BLOCK, CAbstractFactory<CRandbox>::Create(fX, fY, 0.f));
		break;
	case BLK_GUMBA:
		CObjMgr::Get_Instance()->Add_Object(OBJ_TEMP, CAbstractFactory<CGumba>::Create(fX, fY, 0.f));
		break;
	case BLK_TURTLE:
		CObjMgr::Get_Instance()->Add_Object(OBJ_TEMP, CAbstractFactory<CTurtle>::Create(fX, fY, 0.f));
		break;
	case BLK_KOOPA:
		CObjMgr::Get_Instance()->Add_Object(OBJ_TEMP, CAbstractFactory<CKoopa>::Create(fX, fY, 0.f));
		break;
	case BLK_COIN:
		CObjMgr::Get_Instance()->Add_Object(OBJ_COIN, CAbstractFactory<CCoin>::Create(fX, fY, 0.f));
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
	HANDLE		hFile = CreateFile(L"../Data/MapData.dat",
		GENERIC_WRITE,				
		NULL,						
		NULL,						
		CREATE_ALWAYS,				
		FILE_ATTRIBUTE_NORMAL,		
		NULL);						

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, _T("Save File"), _T("Fail"), MB_OK);
		return;
	}
	
	DWORD		dwByte = 0;

	for (auto& iter : m_BlockList)
	{
		bool s = WriteFile(hFile, &iter, sizeof(BlockInfo), &dwByte, nullptr);
		if (!s)
		{
			return;
		}
	}

	CloseHandle(hFile);

	MessageBox(g_hWnd, _T("Save"), _T(""), MB_OK);
}

void CMapEditor::Load()
{
	HANDLE		hFile = CreateFile(L"../Data/MapData.dat",
		GENERIC_READ,				
		NULL,						
		NULL,						
		OPEN_EXISTING,				
		FILE_ATTRIBUTE_NORMAL,		
		NULL);						

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, _T("Load File"), _T("Fail"), MB_OK);
		return;
	}

	DWORD		dwByte = 0;
	BlockInfo		tInfo{};

	while (true)
	{
		bool s = ReadFile(hFile, &tInfo, sizeof(BlockInfo), &dwByte, nullptr);

		if (!s)
		{
			return;
		}

		if (0 == dwByte)
			break;

		m_BlockList.push_back(BlockInfo{ (float)tInfo.fX, (float)tInfo.fY, tInfo.eID });
	}

	CloseHandle(hFile);

	CreateAllBlockInList();
	if(CSceneMgr::Get_Instance()->GetCurScene() == SCENEID::SCENE_EDIT)
		MessageBox(g_hWnd, _T("Load"), _T(""), MB_OK);
}

void CMapEditor::CreateAllBlockInList()
{
	for (auto& iter : m_BlockList)
		CreateBlock(iter.eID, iter.fX, iter.fY);
}
