#pragma once
#include "Obj.h"
class CGumba :
    public CObj
{
public:
	CGumba();
	~CGumba();

public:
	virtual void	Initialize(void)	override;
	virtual int		Update(void)		override;
	virtual	void	Late_Update(void)	override;
	virtual void	Render(HDC hDC)		override;
	virtual void	Release(void)		override;
	virtual void	OnCollision(DIRECTION eDir, CObj* other);

private:

};

