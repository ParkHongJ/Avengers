#pragma once
#include "Obj.h"

class CReflexBullet :
    public CObj
{
public:
	CReflexBullet();
	virtual ~CReflexBullet();

public:
	virtual void Initialize(void) override;
	virtual int	 Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	void	Reflex(DIRECTION eDir);

public:
	virtual	void	OnCollision(DIRECTION eDir, CObj* other);

private:
	bool		m_bIsBouns;

};

