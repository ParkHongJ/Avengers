#pragma once

#include "Include.h"

class CObj
{
public:
	CObj();
	virtual ~CObj();

public:
	void		Set_Pos(float _fX, float _fY)
	{
		m_tInfo.fX = _fX;
		m_tInfo.fY = _fY;
	}
	void		Set_Dir(DIRECTION eDir) { m_eDir = eDir; }
	void		Set_Dead() { m_bDead = true; }
	void		Set_Angle(float _fAngle) { m_fAngle = _fAngle; }
	void		Set_Target(CObj* _pTarget) { m_pTarget = _pTarget; }
	void		Set_Item_Y() {
		m_itembox_y = m_tInfo.fY - m_tInfo.fCY;
	}


	void		Set_PosX(float _fX) { m_tInfo.fX += _fX; }
	void		Set_PosY(float _fY) { m_tInfo.fY += _fY; }

	bool		Get_Dead() { return m_bDead; }
	CObj*		Get_Target() { return m_pTarget; }
	const INFO& Get_Info(void) const { return m_tInfo; }
	const RECT& Get_Rect(void) const { return m_tRect; }


public:
	virtual		void		Initialize(void)	PURE;
	virtual		int			Update(void)		PURE;
	virtual		void		Late_Update(void)	PURE;
	virtual		void		Render(HDC hDC)		PURE;
	virtual		void		Release(void)		PURE;

	virtual	void	OnCollision() {};
	virtual	void	OnCollision(DIRECTION eDir) {};
	virtual	void	OnCollision(CObj* other) {};
	virtual	void	OnCollision(DIRECTION eDir, CObj* other) {};

public:
	virtual void	UpdateGravity();
	virtual void	UpdateGravity(float _fGravity);
	bool CompareTag(string _Tag);
	void SetTag(string _Tag);
protected:
	void		Update_Rect(void);

protected:
	INFO		m_tInfo;
	RECT		m_tRect;

	float		m_fSpeed;
	float		m_fAngle;

	DIRECTION	m_eDir;
	bool		m_bDead;
	string		m_Tag;
	CObj*		m_pTarget;

protected:
	float					m_fGTime;	// 자유 낙하공식의 Time;
	bool					m_bOnAir;
	bool					m_bOnBlock;
	float					m_itembox_y;
};


