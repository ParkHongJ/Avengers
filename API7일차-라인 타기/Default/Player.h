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
	virtual	void OnCollision(DIRECTION eDir);
	virtual void OnCollision(DIRECTION eDir, CObj* other);


private:
	bool					m_bJump;		// ���� ���� Ȯ��
	float					m_fJumpPower;	// ���� ��
	float					m_fGravity;
//hong
// public:
// public:
// 	virtual void Initialize(void) override;
// 	virtual int		Update(void) override;
// 	virtual		void	Late_Update(void);
// 	virtual void Render(HDC hDC) override;
// 	virtual void Release(void) override;
// 	virtual void OnTriggerStay(CObj* other) override;
// private:
// 	void		Key_Input(void);
// 	void		Jumping(void);
 	void		OffSet(void);

// private:
// 	bool					m_bJump;		// ���� ���� Ȯ��
// 	bool					m_bDBJump;		// ���� ���� Ȯ��
// 	float					m_fJumpPower;	// ���� ��
// 	float					m_fJumpTime;	// ���� �� ���� �ð�
// 	POINT					m_tPosin;
// 	float					m_fDiagonal;
// 	bool					m_bOnGrounded;
// 	bool					m_bAbility;
// 	int						m_iJumpCount;

// 	bool					m_bDrawAbility;
// 	bool					m_bOnAir;
// 	int						temp;
// 	CObj*					tempP;
	//bool					m_tempAbility = false;
};

// 1. �÷��̾� ���� ����(�÷��̾� �߽����� �����ϴ� ���� �����ϱ�)
// 2. ��ũ�� �̻��� ����
// 3. �÷��̾ ����ٴϴ� ���� ����(���Լ� ���)
