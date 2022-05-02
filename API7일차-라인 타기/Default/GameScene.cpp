#include "stdafx.h"
#include "GameScene.h"
#include "AbstractFactory.h"

#include "SceneMgr.h"
#include "KeyMgr.h"
#include "MapEditor.h"
#include "ObjMgr.h"
#include "SceneMgr.h"
#include "ScrollMgr.h"
#include "UIMgr.h"
#include "GameMgr.h"

#include "Player.h"
#include "Gumba.h"
#include "CKoopa.h"
#include "Turtle.h"

CGameScene::CGameScene()
{
}

CGameScene::~CGameScene()
{
	Release();
}

void CGameScene::Initailize(void)
{
	CMapEditor::Get_Instance()->Load();
	CUIMgr::Get_Instance()->Initialize();

	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create(150.f,0.f));
	CScrollMgr::Get_Instance()->Initialize();
	CScrollMgr::Get_Instance()->Set_Target(CObjMgr::Get_Instance()->Get_Player());
	
	
	
}

void CGameScene::Update(void)
{
	CObjMgr::Get_Instance()->Update();
	CScrollMgr::Get_Instance()->Update();

	if (CKeyMgr::Get_Instance()->Key_Pressing('I'))
	{
		CSceneMgr::Get_Instance()->ChangeScene(SCENEID::SCENE_START);
	}
}

void CGameScene::Late_Update(void)
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CGameScene::Render(HDC hDC)
{
	CUIMgr::Get_Instance()->GameSceneBackGround(hDC);
	CObjMgr::Get_Instance()->Render(hDC);
	CUIMgr::Get_Instance()->CoinRender(hDC);
	CUIMgr::Get_Instance()->LifeCountRender(hDC);
}

void CGameScene::Release(void)
{
	CObjMgr::Get_Instance()->Release();
	CGameMgr::Get_Instance()->Release();
	CMapEditor::Get_Instance()->Release();

	CUIMgr::Get_Instance()->Release();
	CScrollMgr::Get_Instance()->Release();
}