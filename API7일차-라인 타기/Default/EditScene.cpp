#include "stdafx.h"
#include "EditScene.h"

#include "SceneMgr.h"
#include "KeyMgr.h"
#include "MapEditor.h"
#include "ObjMgr.h"
#include "SceneMgr.h"
#include "ScrollMgr.h"
#include "UIMgr.h"

CEditScene::CEditScene()
{
}

CEditScene::~CEditScene()
{
	Release();
}

void CEditScene::Initailize(void)
{
	CMapEditor::Get_Instance()->Initialize();
	CUIMgr::Get_Instance()->Initialize();
}

void CEditScene::Update(void)
{
	CObjMgr::Get_Instance()->Update();
	CScrollMgr::Get_Instance()->Update();
	CMapEditor::Get_Instance()->Update();

	if (CKeyMgr::Get_Instance()->Key_Pressing('I'))
	{
		CSceneMgr::Get_Instance()->ChangeScene(SCENEID::SCENE_START);
	}
}

void CEditScene::Late_Update(void)
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CEditScene::Render(HDC hDC)
{
	CObjMgr::Get_Instance()->Render(hDC);
	CMapEditor::Get_Instance()->Render(hDC);
}

void CEditScene::Release(void)
{
	CObjMgr::Get_Instance()->Release();
	CMapEditor::Get_Instance()->Release();
	CUIMgr::Get_Instance()->Release();
	CScrollMgr::Get_Instance()->Release();
}