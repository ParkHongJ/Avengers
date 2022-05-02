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

	// ȭ��� ���콺 ��ǥ
	GetCursorPos(&pt);				
	ScreenToClient(g_hWnd, &pt);	

	// ���ӻ� ���콺 ��ǥ
	int iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	m_sMousePos.x = (float)pt.x - iScrollX;
	m_sMousePos.y = (float)pt.y;

	// ���� �� ��ġ
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
		CScrollMgr::Get_Instance()->Set_ScrollX(5.f);
	if (CKeyMgr::Get_Instance()->Key_Pressing('D'))
		CScrollMgr::Get_Instance()->Set_ScrollX(-5.f);

	// �� ���� 1~9
	for (int i = 1; i <= BLOCKID::BLK_END; ++i)
	{
		char temp = 48 + i;
		if (57 < temp) continue;
		if (CKeyMgr::Get_Instance()->Key_Down(temp))
			m_eCurBlockID = (BLOCKID)(i - 1);
	}

	// �� ��ġ
	if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE))
		Edit_CreateBlock();
	// �� ����
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
	// 1. ���� ����

// CreateFile : api ���� ���� �Լ�, ���� ���� �� INVALID_HANDLE_VALUE�ϱ� ������ null������ ����ó���� �� �� ����.

	HANDLE		hFile = CreateFile(L"../Data/MapData.dat",			// ���� ��ο� �̸� ���
		GENERIC_WRITE,				// ���� ���� ��� (GENERIC_WRITE ���� ����, GENERIC_READ �б� ����)
		NULL,						// �������, ������ �����ִ� ���¿��� �ٸ� ���μ����� ������ �� ����� ���ΰ�, NULL�� ��� �������� �ʴ´�
		NULL,						// ���� �Ӽ�, �⺻��	
		CREATE_ALWAYS,				// ���� ���, CREATE_ALWAYS�� ������ ���ٸ� ����, �ִٸ� ���� ����, OPEN_EXISTING ������ ���� ��쿡�� ����
		FILE_ATTRIBUTE_NORMAL,		// ���� �Ӽ�(�б� ����, ���� ��), FILE_ATTRIBUTE_NORMAL �ƹ��� �Ӽ��� ���� �Ϲ� ���� ����
		NULL);						// �������� ������ �Ӽ��� ������ ���ø� ����, �츮�� ������� �ʾƼ� NULL

	if (INVALID_HANDLE_VALUE == hFile)
	{
		// �˾� â�� ������ִ� ����� �Լ�
		// 1. �ڵ� 2. �˾� â�� �������ϴ� �޽��� 3. �˾� â �̸� 4. ��ư �Ӽ�
		MessageBox(g_hWnd, _T("Save File"), _T("Fail"), MB_OK);
		return;
	}

	// 2. ���� ����

	DWORD		dwByte = 0;

	for (auto& iter : m_BlockList)
	{
		WriteFile(hFile, &iter, sizeof(BlockInfo), &dwByte, nullptr);
	}


	// 3. ���� �Ҹ�
	CloseHandle(hFile);

	MessageBox(g_hWnd, _T("Save �Ϸ�"), _T("����"), MB_OK);
}

void CMapEditor::Load()
{
	HANDLE		hFile = CreateFile(L"../Data/MapData.dat",			// ���� ��ο� �̸� ���
		GENERIC_READ,				// ���� ���� ��� (GENERIC_WRITE ���� ����, GENERIC_READ �б� ����)
		NULL,						// �������, ������ �����ִ� ���¿��� �ٸ� ���μ����� ������ �� ����� ���ΰ�, NULL�� ��� �������� �ʴ´�
		NULL,						// ���� �Ӽ�, �⺻��	
		OPEN_EXISTING,				// ���� ���, CREATE_ALWAYS�� ������ ���ٸ� ����, �ִٸ� ���� ����, OPEN_EXISTING ������ ���� ��쿡�� ����
		FILE_ATTRIBUTE_NORMAL,		// ���� �Ӽ�(�б� ����, ���� ��), FILE_ATTRIBUTE_NORMAL �ƹ��� �Ӽ��� ���� �Ϲ� ���� ����
		NULL);						// �������� ������ �Ӽ��� ������ ���ø� ����, �츮�� ������� �ʾƼ� NULL

	if (INVALID_HANDLE_VALUE == hFile)
	{
		// �˾� â�� ������ִ� ����� �Լ�
		// 1. �ڵ� 2. �˾� â�� �������ϴ� �޽��� 3. �˾� â �̸� 4. ��ư �Ӽ�
		MessageBox(g_hWnd, _T("Load File"), _T("Fail"), MB_OK);
		return;
	}

	// 2. ���� ����

	DWORD		dwByte = 0;
	BlockInfo		tInfo{};

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(BlockInfo), &dwByte, nullptr);

		if (0 == dwByte)	// ���̻� ���� �����Ͱ� ���� ���
			break;

		m_BlockList.push_back(BlockInfo{ (float)tInfo.fX, (float)tInfo.fY, tInfo.eID });
	}


	// 3. ���� �Ҹ�
	CloseHandle(hFile);

	CreateAllBlockInList();
	MessageBox(g_hWnd, _T("Load �Ϸ�"), _T("����"), MB_OK);
}

void CMapEditor::CreateAllBlockInList()
{
	for (auto& iter : m_BlockList)
		CreateBlock(iter.eID, iter.fX, iter.fY);
}
