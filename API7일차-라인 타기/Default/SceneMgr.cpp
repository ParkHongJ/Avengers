#include "stdafx.h"
#include "SceneMgr.h"

#include "StartScene.h"
#include "GameScene.h"
#include "EditScene.h"
#include "BossScene.h"

CSceneMgr* CSceneMgr::m_pInstance = nullptr;

CSceneMgr::CSceneMgr()
{
}

CSceneMgr::~CSceneMgr()
{
	Release();
}

void CSceneMgr::Initailize(void)
{
	m_eCurScene = SCENEID::SCENE_START;

	m_SceneList[SCENEID::SCENE_START] = new CStartScene;
	m_SceneList[SCENEID::SCENE_PLAYE] = new CGameScene;
	m_SceneList[SCENEID::SCENE_EDIT] = new CEditScene;
	m_SceneList[SCENEID::SCENE_BOSS] = new CBossScene;

	m_SceneList[m_eCurScene]->Initailize();
}

void CSceneMgr::Update(void)
{
	m_SceneList[(int)m_eCurScene]->Update();
}

void CSceneMgr::Late_Update(void)
{
	m_SceneList[(int)m_eCurScene]->Late_Update();
}

void CSceneMgr::Render(HDC hDC)
{
	m_SceneList[(int)m_eCurScene]->Render(hDC);
}

void CSceneMgr::Release(void)
{
	for (int i = 0; i < SCENEID::SCENE_REAL_END; ++i)
	{
		if (i == SCENE_END)
			continue;

		Safe_Delete<CScene*>(m_SceneList[i]);
	}
}

void CSceneMgr::ChangeScene(int eScene)
{
	if (SCENE_END == eScene)
	{
		PostQuitMessage(0);
		return;
	}
		
	m_SceneList[(int)m_eCurScene]->Release();
	m_eCurScene = (SCENEID)eScene;
	m_SceneList[(int)m_eCurScene]->Initailize();
}