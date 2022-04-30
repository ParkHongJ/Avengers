#pragma once
#include "Include.h"
#include "Obj.h"

class CScrollMgr
{
private:
	CScrollMgr();
	~CScrollMgr();

public:
	float		Get_ScrollX(void) { return m_fScrollX; }
	void		Set_ScrollX(float _fX) { m_fScrollX += _fX; }
	void		Set_Target(CObj* _pTarget) { m_pTarget = _pTarget; }

public:
	static		CScrollMgr* Get_Instance(void)
	{
		if (!m_pInstance)
		{
			m_pInstance = new CScrollMgr;
		}

		return m_pInstance;
	}

	static	void	Destroy_Instance(void)
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

public:
	void	Update(void);
	void	Initialize(void);

private:
	static CScrollMgr* m_pInstance;

	CObj*					m_pTarget;
	float					m_fScrollX;
};

