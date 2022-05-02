#pragma once
#include "Include.h"

class CScene
{
public:
	CScene();
	virtual ~CScene();

public:
	virtual void		Initailize(void)	PURE;
	virtual void		Update(void)		PURE;
	virtual void		Late_Update(void)	PURE;
	virtual void		Render(HDC hDC)		PURE;
	virtual void		Release(void)		PURE;
};

