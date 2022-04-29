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


private:
	void		Key_Input(void);

public:
	virtual void OnCollision();
	virtual	void	OnCollision(DIRECTION eDir);

private:
	bool					m_bJump;		// 점프 상태 확인
	float					m_fJumpPower;	// 점프 힘

};