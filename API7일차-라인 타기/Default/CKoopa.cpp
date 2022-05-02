#include "stdafx.h"
#include "CKoopa.h"
#include <time.h>
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "Bullet.h"
#include "resource.h"
#include "ScrollMgr.h"
CKoopa::CKoopa()
{
	srand(unsigned int(time(NULL)));
}

CKoopa::~CKoopa()
{
}

void CKoopa::Initialize(void)
{
	//현재상태
	m_pTarget = nullptr;

	m_eCurrentState = IdleState;
	m_Sprite = IDB_KOOPA_IDLE_LEFT;

	m_tInfo.fX = 400.f;
	m_tInfo.fY = 0.f;

	m_tInfo.fCX = 140.f;
	m_tInfo.fCY = 150.f;
	m_fSpeed = 1.5f;
	m_fTurtleSpeed = 3.f;
	m_Tag = "Monster";
	m_fJumpPower = 0.f;
	m_bJump = false;
	m_bTurtle = false;
	m_iHp = 3;
	m_BulletDelay = GetTickCount();
	
	//대기상태 카운트 이유: 랜덤으로 뽑기때문에 계속 Idle뽑힐 가능성이 있음. 그래서 넣어둠
	IdleCount = 0;

	//패턴 강제실행
	m_bActivatePattern = false;
}

int CKoopa::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;
	switch (m_eCurrentState)
	{
	case IdleState:
		if (m_pTarget != NULL && m_tInfo.fX > m_pTarget->Get_Info().fX)
		{
			m_Sprite = IDB_KOOPA_IDLE_LEFT;
		}
		else
		{
			m_Sprite = IDB_KOOPA_IDLE_RIGHT;
		}
		IdleCount++;
		if (IdleCount >= 2)
		{
			m_bActivatePattern = true;
			break;
		}
		m_bTurtle = false;
		break;
	case Chase:
		if (m_pTarget != nullptr)
		{
			if (m_pTarget->Get_Info().fX <= m_tInfo.fX)
			{
				m_tInfo.fX -= m_fSpeed;
			}
			else if (m_pTarget->Get_Info().fX >= m_tInfo.fX)
			{
				m_tInfo.fX += m_fSpeed;
			}
		}
		else
		{
			m_bActivatePattern = true;
		}
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
		m_Sprite = IDB_KOOPA_TURTLE;
		if (m_tInfo.fX <= 100 || m_tInfo.fX >= WINCX - 100)
		{
			m_fTurtleSpeed *= -1.f;
		}
		m_tInfo.fX += m_fTurtleSpeed;
		break;
	case Jump:
		m_bActivatePattern = true;
		m_fJumpPower = 10.f;
		m_bJump = true;
		break;
	case BulletUpFire:
		if (m_bTurtle)
		{
			m_bActivatePattern = true;
			break;
		}
		if (m_pTarget != NULL && m_tInfo.fX > m_pTarget->Get_Info().fX)
		{
			m_Sprite = IDB_KOOPA_IDLE_LEFT;
		}
		else
		{
			m_Sprite = IDB_KOOPA_IDLE_RIGHT;
		}
		if (GetTickCount() - m_BulletDelay >= 100)
		{
			if (m_fBulletAngle >= 140.f)
			{
				break;
			}
			CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET,
				CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY - m_tInfo.fCY * .5f,
					m_fBulletAngle += 10));
			m_BulletDelay = GetTickCount();
		}
		break;
	case BulletPlayerFire:
		if (m_pTarget != NULL && m_tInfo.fX > m_pTarget->Get_Info().fX)
		{
			m_Sprite = IDB_KOOPA_IDLE_LEFT;
		}
		else
		{
			m_Sprite = IDB_KOOPA_IDLE_RIGHT;
		}
		//int m_fDistance = (m_pTarget->Get_Info().fX - m_tInfo.fX) + (m_pTarget->Get_Info().fY - m_tInfo.fY);
		//m_fAngle = m_pTarget->Get_Info().fX
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
	CObj::UpdateGravity(4.0f);

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
	HDC MemDC;
	HBITMAP MyBitmap, OldBitmap;
	int iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	m_tRect.right += iScrollX - 5;
	m_tRect.left += iScrollX + 5;
	MemDC = CreateCompatibleDC(hDC);
	MyBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(m_Sprite));
	OldBitmap = (HBITMAP)SelectObject(MemDC, MyBitmap);

	
	GdiTransparentBlt(hDC, m_tRect.left, m_tRect.top, 150, 150, MemDC, 0, 0, 150, 150, RGB(255, 255, 255));

	SelectObject(MemDC, OldBitmap);
	DeleteObject(MyBitmap);
	DeleteDC(MemDC);
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
		if (other->CompareTag("Player"))
		{
			if (m_eCurrentState == Turtle || m_eCurrentState == TutleChase)
			{
				//거북이거나 거북이 쫓고있을때 위에서 내려찍으면 플레이어가 데미지 입어야함
				break;
			}
			m_iHp--;
			m_Sprite = IDB_KOOPA_HIT;
			m_eCurrentState = HIT;
			if (m_iHp <= 0)
			{
				m_eCurrentState = Dead;
			}
		}
		break;
	case DIR_DOWN:
		if (m_eCurrentState == TutleChase)
			break;
		break;
	case DIR_LEFT:
		break;
	case DIR_RIGHT:
		break;
	default:
		break;
	}
}
