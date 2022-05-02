#pragma once
#include  "Obj.h"
#include "GameMgr.h"
class CCoin : public CObj
{
public:
	CCoin();
	~CCoin();
public:
	void		Initialize(void);
	int			Update(void);
	void		Late_Update(void);
	void		Render(HDC hDC);
	void		Release(void);

public:
	// 기존의 온콜리전 삭제 
	void	OnCollision(CObj* other);
	



};

