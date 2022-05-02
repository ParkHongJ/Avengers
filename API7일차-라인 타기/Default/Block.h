#pragma once
#include "Obj.h"
class CBlock :
	public CObj
{
public:
	CBlock();
	virtual ~CBlock();

public:
	virtual void	Initialize(void)	override;
	virtual int		Update(void)		override;
	virtual	void	Late_Update(void)	override;
	virtual void	Render(HDC hDC)		override;
	virtual void	Release(void)		override;

public:
	virtual void	OnCollision();
	virtual	void	OnCollision(DIRECTION eDir);

private:
	float m_fItemSpeed = 0.f;
	RECT m_tItemRect;
	INFO m_tItemInfo;
	int m_Sprite;
};
