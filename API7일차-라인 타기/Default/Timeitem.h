#pragma once
#include "Obj.h"
class CTimeitem : public CObj
{
public:
	CTimeitem();
	~CTimeitem();

public:
	void		Initialize(void);
	int			Update(void);
	void		Late_Update(void);
	void		Render(HDC hDC);
	void		Release(void);

public:
	// ������ ���ݸ��� ���� 
	void	OnCollision(CObj* other);

private:
	int m_Sprite;
};

