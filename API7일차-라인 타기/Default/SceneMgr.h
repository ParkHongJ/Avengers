#pragma once

#include "Scene.h"

class CSceneMgr
{
private:
	CSceneMgr();
	~CSceneMgr();

public:
	static		CSceneMgr* Get_Instance(void)
	{
		if (!m_pInstance)
		{
			m_pInstance = new CSceneMgr;
		}

		return m_pInstance;
	}

	static	void	Destroy_Instance(void)
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

public:
	void	ChangeScene(int eScene);
	SCENEID GetCurScene() { return m_eCurScene; }

public:
	void		Initailize(void);
	void		Update(void);
	void		Late_Update(void);
	void		Render(HDC hDC);
	void		Release(void);

private:
	static CSceneMgr* m_pInstance;

private:
	CScene*     	m_SceneList[SCENE_END];
	SCENEID			m_eCurScene;
};

