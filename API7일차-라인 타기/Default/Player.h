#pragma once

#include "Obj.h"
#include "Resource.h"
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
	void		SniperRender(HDC hDC);

public:
	virtual void OnCollision(DIRECTION eDir, CObj* other);

public:     //�μ����� �÷��̾� ���׾Ƹ� Ŀ���� �ڵ� 
	//���۸������϶� ���Ѽ���
	const int GetState() { return m_Sprite; };
	void UpGradeBody() { m_tInfo.fCX += 1.0; m_tInfo.fCY += 1.0;
	m_Sprite = IDB_SUPERMARIO; }
	void DownGradeBody() { m_tInfo.fCX -= 1.0; m_tInfo.fCY -= 1.0;
	m_Sprite = IDB_SMALLMARIO; }
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
	int						m_Sprite;

	bool	m_bDieTrigger;
};