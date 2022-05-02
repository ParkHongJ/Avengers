#pragma once
#include "Obj.h"
#include "SCrollMgr.h"
#include "GameMgr.h"
#include "ObjMgr.h"
#include "Coin.h"
#include "AbstractFactory.h"
#include "Mushroom.h"
#include "Timeitem.h"
class CRandbox : public CObj
{
public:
	CRandbox();
	~CRandbox();
	
public:
	void		Initialize(void);
	int			Update(void);
	void		Late_Update(void);
	void		Render(HDC hDC);
	void		Release(void);

public:
	void	OnCollision(DIRECTION eDir, CObj* other);
	
private:
	bool m_bCheck;
};

