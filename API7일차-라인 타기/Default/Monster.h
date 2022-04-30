#pragma once
#include "Obj.h"

class CMonster :
	public CObj
{
public:
	CMonster();
	virtual ~CMonster();


public:
	void SetTarget(CObj* _pTarget) { m_pTarget = _pTarget; }


public:
	virtual void	Initialize(void)	override;
	virtual int		Update(void)		override;
	virtual	void	Late_Update(void)	override;
	virtual void	Render(HDC hDC)		override;
	virtual void	Release(void)		override;


	virtual void OnCollision(DIRECTION eDir) {};
	virtual void OnCollision(DIRECTION eDir, CObj* other);

public:
	virtual void OnCollision();

private:
	float m_fItemSpeed = 0.f;
	RECT m_tItemRect;
	INFO m_tItemInfo;

};



