#pragma once
#include "Scene.h"
class CEditScene :
    public CScene
{
public:
	CEditScene();
	~CEditScene();

public:
	virtual void		Initailize(void);
	virtual void		Update(void);
	virtual void		Late_Update(void);
	virtual void		Render(HDC hDC);
	virtual void		Release(void);

private:


};

