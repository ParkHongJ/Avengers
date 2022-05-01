#pragma once

#include "Obj.h"

class CPlayer :
	public CObj
{
public:
	CPlayer();
	virtual ~CPlayer();

public:
	virtual void	Initialize(void)	override;
	virtual int		Update(void)		override;
	virtual	void	Late_Update(void)	override;
	virtual void	Render(HDC hDC)		override;
	virtual void	Release(void)		override;


public:
	void		Set_RelexBulletToNull() { m_pRelexBullet = nullptr; }

private:
	void		Key_Input(void);
	void		OffSet(void);
	void		SniperRender(HDC hDC);

public:
	virtual void OnCollision();
	virtual	void OnCollision(DIRECTION eDir);
	virtual void OnCollision(DIRECTION eDir, CObj* other);

private:
	bool					m_bJump;
	float					m_fJumpPower;
	bool					m_bSniperMode;

	POINT					m_tPosin;
	CObj*					m_pRelexBullet;
};