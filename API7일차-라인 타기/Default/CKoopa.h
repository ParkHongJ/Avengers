#pragma once
#include "Obj.h"
enum KooPaState
{
	IdleState = 1,
	Chase,
	Turtle, //거북이로 변신하기
	TutleChase, // 거북이껍데기로 바뀌어서 플레이어 N초동안 이동하기
	Jump, // 거북이껍데기로 바뀌어서 플레이어 방향으로 점프하기 기본상태일때도 점프함
	BulletUpFire, // 위로 1초마다 20발정도 쏘고 산성비처럼 총알이떨어짐
	BulletPlayerFire, // 플레이어 방향으로 총알 N초마다 1발씩 3번쏘기
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

