#pragma once
#include "Obj.h"
enum KooPaState
{
	IdleState = 1,
	Chase,
	Turtle, //�ź��̷� �����ϱ�
	TutleChase, // �ź��̲������ �ٲ� �÷��̾� N�ʵ��� �̵��ϱ�
	Jump, // �ź��̲������ �ٲ� �÷��̾� �������� �����ϱ� �⺻�����϶��� ������
	BulletUpFire, // ���� 1�ʸ��� 20������ ��� �꼺��ó�� �Ѿ��̶�����
	BulletPlayerFire, // �÷��̾� �������� �Ѿ� N�ʸ��� 1�߾� 3�����
	HIT,
	Dead
};
class CKoopa :
    public CObj
{
public:
	CKoopa();
	~CKoopa();
public:
	virtual void	Initialize(void)	override;
	virtual int		Update(void)		override;
	virtual	void	Late_Update(void)	override;
	virtual void	Render(HDC hDC)		override;
	virtual void	Release(void)		override;
	virtual void	OnCollision(DIRECTION eDir, CObj* other);

private:
	float m_fJumpPower;
	bool m_bJump;
	KooPaState m_eCurrentState;
	DWORD m_fPatternTimer;
	int m_iHp;
	bool m_bTurtle = false;
	DWORD m_BulletDelay;
	float m_fBulletAngle = 10.f;
	bool m_bActivatePattern;
	int IdleCount;
	float m_fTurtleSpeed;

	int m_Sprite;

	float m_fHitTime;
};

