#include "stdafx.h"
#include "SceneMgr.h"

#include "StartScene.h"
#include "GameScene.h"
#include "EditScene.h"

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
	m_SceneList[SCENEID::SCENE_START] = new CStartScene;
	m_SceneList[SCENEID::SCENE_PLAYE] = new CGameScene;
	m_SceneList[SCENEID::SCENE_EDIT] = new CEditScene;

	m_eCurScene = SCENEID::SCENE_START;
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
	for (int i = 0; i < SCENEID::SCENE_END; ++i)
	{
		Safe_Delete<CScene*>(m_SceneList[i]);
	}
}

void CSceneMgr::ChangeScene(SCENEID eScene)
{
	m_SceneList[(int)m_eCurScene]->Release();
	m_eCurScene = eScene;
	m_SceneList[(int)m_eCurScene]->Initailize();
}