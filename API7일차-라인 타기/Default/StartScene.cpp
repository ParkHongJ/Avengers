#include "stdafx.h"
#include "StartScene.h"

#include "SceneMgr.h"
#include "KeyMgr.h"
#include "UIMgr.h"

CStartScene::CStartScene()
{
}

CStartScene::~CStartScene()
{
	Release();
}

void CStartScene::Initailize(void)
{
	CUIMgr::Get_Instance()->Initialize();
	m_eCurScene = SCENE_PLAYE;
}

void CStartScene::Update(void)
{
	if (CKeyMgr::Get_Instance()->Key_Down(VK_UP))
	{
		--m_eCurScene;
		if (m_eCurScene <= 1)
			m_eCurScene = 1;
	}
	else if (CKeyMgr::Get_Instance()->Key_Down(VK_DOWN))
	{
		++m_eCurScene;
		if (m_eCurScene >= SCENE_END)
			m_eCurScene = SCENE_END;
	}

	if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE))
	{
		CSceneMgr::Get_Instance()->ChangeScene((SCENEID)m_eCurScene);
	}

}

void CStartScene::Late_Update(void)
{
}

void CStartScene::Render(HDC hDC)
{
	CUIMgr::Get_Instance()->StartSceneBackGround(hDC);
	CUIMgr::Get_Instance()->StartSceneRender(hDC, (SCENEID)m_eCurScene);

}

void CStartScene::Release(void)
{
	CUIMgr::Get_Instance()->Release();
}
