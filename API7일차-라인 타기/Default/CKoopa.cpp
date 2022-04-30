#include "stdafx.h"
#include "CKoopa.h"
#include <time.h>
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "Bullet.h"
CKoopa::CKoopa()
{
	srand(unsigned int(time(NULL)));
}

CKoopa::~CKoopa()
{
}

void CKoopa::Initialize(void)
{
	m_eCurrentState = IdleState;
	m_tInfo.fX = 400.f;
	m_tInfo.fY = 0.f;

	m_tInfo.fCX = 150.f;
	m_tInfo.fCY = 150.f;
	m_fSpeed = 5.f;
	m_Tag = "Monster";
	m_fJumpPower = 0.f;
	m_bJump = false;
	m_bTurtle = false;
	m_iHp = 3;
	m_BulletDelay = GetTickCount();
	m_bActivatePattern = false;
	IdleCount = 0;
}

int CKoopa::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;
	switch (m_eCurrentState)
	{
	case IdleState:
		IdleCount++;
		if (IdleCount >= 2)
		{
			m_bActivatePattern = true;
			break;
		}
		m_bTurtle = false;
		break;
	case Chase:
		break;
	case Turtle:
		m_bTurtle = true;
		IdleCount++;
		if (IdleCount >= 2)
		{
			m_bActivatePattern = true;
			break;
		}
		break;
	case TutleChase:
		if (!m_bTurtle)
		{
			m_bActivatePattern = true;
			break;
		}
		if (m_tInfo.fX <= 50 || m_tInfo.fX >= WINCX - 50)
		{
			m_fSpeed *= -1.f;
		}
		m_tInfo.fX += m_fSpeed;
		break;
	case TutlreJump:
		break;
	case BulletUpFire:
		if (m_bTurtle)
		{
			m_bActivatePattern = true;
			break;
		}
		if (GetTickCount() - m_BulletDelay >= 100)
		{
			if (m_fBulletAngle >= 140.f)
			{
				break;
			}
			CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET,
				CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY - m_tInfo.fCY * .5f,
					m_fBulletAngle += 10));//rand() % (130 + 1 - 70) + 50));
			m_BulletDelay = GetTickCount();
		}
		
		break;
	case BulletPlayerFire:
		break;
	case Dead:
		return OBJ_DEAD;
	default:
		break;
	}
	Update_Rect();
	return OBJ_NOEVENT;
}

void CKoopa::Late_Update(void)
{
	CObj::UpdateGravity(6.0f);

	if (m_bJump)
	{
		m_tInfo.fY -= m_fJumpPower * sinf((90.f * PI) / 180.f);
	}
	//m_eCurrentState = BulletUpFire;
	if (GetTickCount() - m_fPatternTimer >= 6000 || m_bActivatePattern)
	{
		m_eCurrentState = (KooPaState)(rand() % 7 + 1);
		m_fPatternTimer = GetTickCount();
		m_BulletDelay = GetTickCount();
		m_fBulletAngle = 10.f;
		m_bActivatePattern = false;
		IdleCount = 0;
	}
}

void CKoopa::Render(HDC hDC)
{
	if (!m_bTurtle)
	{
		Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	}
	else if(m_bTurtle)
	{
		Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	}
}

void CKoopa::Release(void)
{
}

void CKoopa::OnCollision(DIRECTION eDir, CObj* other)
{
	switch (eDir)
	{
	case DIR_UP:
		m_bOnBlock = true;
		m_bJump = false;
		m_fJumpPower = 0.f;
		break;
	case DIR_DOWN:
		if (other->CompareTag("Player"))
		{
			m_iHp--;
			if (m_iHp <= 0)
			{
				m_eCurrentState = Dead;
			}
			m_eCurrentState = Turtle;
		}
		break;
	case DIR_LEFT:
		break;
	case DIR_RIGHT:
		break;
	default:
		break;
	}
}
