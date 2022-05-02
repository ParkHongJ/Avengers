#pragma once
#include "Scene.h"

class CStartScene :
    public CScene
{
public:
    CStartScene();
    ~CStartScene();

public:
	virtual void		Initailize(void);
	virtual void		Update(void);
	virtual void		Late_Update(void);
	virtual void		Render(HDC hDC);
	virtual void		Release(void);

private:
	int		m_eCurScene;

};

