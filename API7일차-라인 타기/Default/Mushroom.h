#pragma once
#include "Obj.h"
#include "GameMgr.h"

class CMushroom : public CObj
{
public:
	CMushroom();
	~CMushroom();

public:
	void		Initialize(void);
	int			Update(void);
	void		Late_Update(void);
	void		Render(HDC hDC);
	void		Release(void);
public:
	void	OnCollision(CObj* other);
};

