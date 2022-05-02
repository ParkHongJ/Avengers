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

public:     //민성전용 플레이어 몸뚱아리 커지는 코드 
	void UpGradeBody() { m_tInfo.fCX += 1.0; m_tInfo.fCY += 1.0; }
	void DownGradeBody() { m_tInfo.fCX -= 1.0; m_tInfo.fCY -= 1.0; }
	void UpLife();
	void DownLife();

	void DieDie();
	void Die();

private:
	bool					m_bJump;
	float					m_fJumpPower;
	bool					m_bSniperMode;
    float					m_fGravity;

	int						m_fLifeCount;

	POINT					m_tPosin;
	CObj*					m_pRelexBullet;

	bool	m_bDieTrigger;
};