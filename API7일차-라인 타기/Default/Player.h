#pragma once
#include "Obj.h"
#include "Bullet.h"

class CPlayer : public CObj
{
public:
	CPlayer();
	virtual ~CPlayer();

public:
	void	Set_BulletList(list<CObj*>* pBullet)
	{
		m_pBullet = pBullet;
	}
	void	Set_ShieldList(list<CObj*>* pShield) { m_pShield = pShield; }

public:
	virtual void Initialize(void) override;
	virtual int		Update(void) override;
	virtual		void	Late_Update(void);
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
	virtual void OnTriggerStay(CObj* other) override;
	void Jump(void);
private:
	void		Key_Input(void);

	CObj*		Create_Shield(void);

	template<typename T>
	CObj*		Create_Bullet(void);

private:
	typedef list<CObj*>		BULLETLIST;
	BULLETLIST*				m_pBullet;

	list<CObj*>*			m_pShield;

	POINT					m_tPosin;
	float					m_fDiagonal;
	bool					m_bJump;
	float m_tempSpeed = 2.5f;
	POINT tempLineL = { 100, 100 };
	POINT tempLineR = { 400, 100};
};

// 1. �÷��̾� ���� ����(�÷��̾� �߽����� �����ϴ� ���� �����ϱ�)
// 2. ��ũ�� �̻��� ����
// 3. �÷��̾ ����ٴϴ� ���� ����(���Լ� ���)


// �Լ�		: ���, Input�� Output�� ����		Y = F(X)	-> y = x + 1
// �ﰢ �Լ�  : �����ڵ��� ã�� ����, �غ�, ���� ���̿� ���踦 �ǹ�, ���� ���� �˸� �� ���̿� �������� ���踦 ������ ���� �Լ�
