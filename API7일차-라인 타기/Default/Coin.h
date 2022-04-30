#pragma once
#include  "Obj.h"
class CCoin : public CObj 
{
public:
	 CCoin();
	~CCoin();
public:
	void		Initialize(void);
	int			Update(void);
	void		Late_Update(void);
	void		Render(HDC hDC);
	void		Release(void);
public:
	virtual void	OnCollision();    
	virtual	void	OnCollision(DIRECTION eDir);

public:
	
};

