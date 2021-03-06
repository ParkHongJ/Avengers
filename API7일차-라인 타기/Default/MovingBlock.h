#pragma once
#include "Obj.h"

class CMovingBlock :
	public CObj
{
public:
	CMovingBlock();
    virtual ~CMovingBlock();

public:
	virtual void	Initialize(void)	override;
	virtual int		Update(void)		override;
	virtual	void	Late_Update(void)	override;
	virtual void	Render(HDC hDC)		override;
	virtual void	Release(void)		override;

public:
	virtual void	OnCollision();
	virtual	void	OnCollision(DIRECTION eDir);
	virtual	void	OnCollision(DIRECTION eDir, CObj* other);

private:
	CObj*	m_pPlayer;
	float m_fCenter_Pos;
	bool  m_bCenter_Check;
	int m_Sprite;
};

