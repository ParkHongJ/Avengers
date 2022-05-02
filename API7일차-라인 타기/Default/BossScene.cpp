#include "stdafx.h"
#include "BossScene.h"
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
#include "Block.h"

CBossScene::CBossScene()
{
}

CBossScene::~CBossScene()
{
	Release();
}

void CBossScene::Initailize(void)
{
	CUIMgr::Get_Instance()->Initialize();

	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create(100.f, 0.f));
	CScrollMgr::Get_Instance()->Initialize();
	CScrollMgr::Get_Instance()->Set_Target(CObjMgr::Get_Instance()->Get_Player());

	for (int i = 0; i < 102; ++i)
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_BLOCK, CAbstractFactory<CBlock>::Create(32 * i, 600 - 64.f));
	}
	CObjMgr::Get_Instance()->Add_Object(OBJ_TEMP, CAbstractFactory<CKoopa>::Create(800, 100));

}

void CBossScene::Update(void)
{
	CObjMgr::Get_Instance()->Update();
	CScrollMgr::Get_Instance()->Update();

	if (CKeyMgr::Get_Instance()->Key_Pressing('I'))
	{
		CSceneMgr::Get_Instance()->ChangeScene(SCENEID::SCENE_START);
	}
}

void CBossScene::Late_Update(void)
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CBossScene::Render(HDC hDC)
{
	CUIMgr::Get_Instance()->BossSceneBackGround(hDC);
	CObjMgr::Get_Instance()->Render(hDC);
	CUIMgr::Get_Instance()->CoinRender(hDC);
	CUIMgr::Get_Instance()->LifeCountRender(hDC);
}

void CBossScene::Release(void)
{
	CGameMgr::Get_Instance()->Release();
	CObjMgr::Get_Instance()->Release();
	CMapEditor::Get_Instance()->Release();
	CUIMgr::Get_Instance()->Release();
	CScrollMgr::Get_Instance()->Release();
}