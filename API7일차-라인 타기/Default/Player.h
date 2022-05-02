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

public:     //민성전용 플레이어 몸뚱아리 커지는 코드 
	void UpGradeBody() {
		m_tInfo.fCX *= 1.3; m_tInfo.fCY *= 1.3; 
		m_Sprite = IDB_SUPERMARIO;
	}
	//슈퍼마리오일때 벽뿌수기
	const int GetState() { return m_Sprite; };

private:
	bool					m_bJump;
	float					m_fJumpPower;
	bool					m_bSniperMode;
	float					m_fGravity;


	POINT					m_tPosin;
	CObj*					m_pRelexBullet;
	int						m_Sprite;
};