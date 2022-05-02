#include "stdafx.h"
#include "Player.h"
#include "AbstractFactory.h"

#include "KeyMgr.h"
#include "ObjMgr.h"
#include "LineMgr.h"

#include "ScrollMgr.h" 
#include "MainGame.h"
#include "ReflexBullet.h"
#include "UIMgr.h"

CPlayer::CPlayer()
{
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize(void)
{
	m_pRelexBullet = nullptr;
	m_tInfo.fX = 0.f;
	m_tInfo.fY = 0.f;

	m_tInfo.fCX = 32.f;
	m_tInfo.fCY = 32.f;

	m_fSpeed = 5.f;

	m_bSniperMode = false;
	m_bJump = false;
	m_fJumpPower = 10.f;

	m_Tag = "Player";
	m_fGravity = 9.8f;

	// m_Sprite = IDB_SMALLMARIO;
	m_Sprite = IDB_SUPERMARIO;
	m_fSmallY = 16;
	m_fBigY = 32;

	m_bUnbtb = false;
	m_fOldTime = GetTickCount64();
	m_fUnbtbTime = 3000.f;

	m_fAngle = 0;

	m_bDieTrigger = false;

	m_fLifeCount = 2;
	CUIMgr::Get_Instance()->SetLifeCount(m_fLifeCount);

}

int CPlayer::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;
		

	if (m_fOldTime + m_fUnbtbTime < GetTickCount64() && m_bUnbtb)
	{
		m_bUnbtb = false;

		if (m_Sprite == IDB_SUPER_UNTBT&& m_bUnbtb)
			m_Sprite = IDB_SUPERMARIO;
		else if (m_Sprite == IDB_SMALL_UNTBT && m_bUnbtb)
			m_Sprite = IDB_SMALLMARIO;
	}


	Key_Input();

	Update_Rect();

	return OBJ_NOEVENT;
}

void CPlayer::Late_Update(void)
{
	CObj::UpdateGravity(m_fGravity);

	if (m_bJump)
	{
		m_tInfo.fY -= m_fJumpPower * sinf((90.f * PI) / 180.f);
	}

	DieDie();
}

void CPlayer::DieDie()
{
	// �׾��� ��
	if (m_tInfo.fY >= WINCY && !m_bDieTrigger)
	{
		m_bDieTrigger = true;
		m_fGTime = 0.f;
	}
	else if (m_bDieTrigger)
	{
		m_bJump = true;
		m_fJumpPower = 10.f;
		m_fGravity = 9.8f;
	}

	if (m_tInfo.fY >= WINCY + 500)
	{
		Die();
	}
}
void CPlayer::Die()
{
	DownLife();

	m_fGTime = 0.f;
	m_tInfo.fX = 400.f;
	m_tInfo.fY = 100.f;
	m_bDieTrigger = false;
}

void CPlayer::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	HDC MemDC;
	HBITMAP MyBitmap, OldBitmap;
	m_tRect.right += iScrollX - 5;
	m_tRect.left += iScrollX + 5;
	MemDC = CreateCompatibleDC(hDC);

	if (m_Sprite == IDB_SUPERMARIO && m_bUnbtb)
		m_Sprite = IDB_SUPER_UNTBT;
	else if (m_Sprite == IDB_SMALLMARIO && m_bUnbtb)
		m_Sprite = IDB_SMALL_UNTBT;

	MyBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(m_Sprite));
	OldBitmap = (HBITMAP)SelectObject(MemDC, MyBitmap);

	if (m_Sprite == IDB_SUPER_UNTBT || m_Sprite == IDB_SUPERMARIO)
		TransparentBlt(hDC, m_tRect.left, m_tRect.top - 32, 32, 64, MemDC, 0, 0, 16, m_fBigY, RGB(255, 255, 255));
	else if (m_Sprite == IDB_SMALL_UNTBT || m_Sprite == IDB_SMALLMARIO)
		TransparentBlt(hDC, m_tRect.left, m_tRect.top, 32, 32, MemDC, 0, 0, 16, m_fSmallY, RGB(255, 255, 255));

	SelectObject(MemDC, OldBitmap);
	DeleteObject(MyBitmap);
	DeleteDC(MemDC);
	SniperRender(hDC);
}

void CPlayer::SniperRender(HDC hDC)
{
	if (!m_bSniperMode)
		return;

	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();

	m_tPosin.x = long(m_tInfo.fX + 30.f * cosf((m_fAngle * PI) / 180.f));
	m_tPosin.y = long(m_tInfo.fY - 30.f * sinf((m_fAngle * PI) / 180.f));

	MoveToEx(hDC, (int)m_tInfo.fX + iScrollX, (int)m_tInfo.fY, nullptr);
	LineTo(hDC, (int)m_tPosin.x + iScrollX, (int)m_tPosin.y);
}


void CPlayer::Key_Input(void)
{
	//if (CKeyMgr::Get_Instance()->Key_Down('B'))
	//{
	//	m_bJump = true;
	//	m_fJumpPower = 5.f;
	//	m_fGTime = 0.f;
	//}
	// SnipingMode
	if (CKeyMgr::Get_Instance()->Key_Pressing('R') && m_pRelexBullet)
	{
		m_tInfo.fX = m_pRelexBullet->Get_Info().fX;
		m_tInfo.fY = m_pRelexBullet->Get_Info().fY;
		m_pRelexBullet->Set_Dead();
		m_pRelexBullet = nullptr;
	}
	// Sniping
	if (CKeyMgr::Get_Instance()->Key_Up('W') && m_bSniperMode && !m_pRelexBullet)
	{
		m_bSniperMode = false;
		m_pRelexBullet = CAbstractFactory<CReflexBullet>::Create(m_tInfo.fX, m_tInfo.fY, m_fAngle);
		m_pRelexBullet->Set_Target(this);
		CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, m_pRelexBullet);
	}
	// SnipingMode
	if (CKeyMgr::Get_Instance()->Key_Pressing('W') && !m_pRelexBullet)
	{
		m_bSniperMode = true;

		if (CKeyMgr::Get_Instance()->Key_Pressing('Q'))
			m_fAngle += 1.5f;
		if (CKeyMgr::Get_Instance()->Key_Pressing('E'))
			m_fAngle -= 1.5f;
	}
	if (CKeyMgr::Get_Instance()->Key_Down('V'))
	{
		if (CMainGame::m_fTime == 0.1f)
			CMainGame::m_fTime = 1.f;
		else
			CMainGame::m_fTime = 0.1f;
	}
	if (CKeyMgr::Get_Instance()->Key_Down(VK_DOWN))
	{
		if (m_bJump && m_tInfo.fY <= 300.f)
		{
			m_fGravity = 15.f;
		}
	}
	
	
	// Jump
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_SPACE) && !m_bJump)
	{
		m_fJumpPower = 12.f;
		m_bJump = true;
	}

	// Move
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
		m_tInfo.fX -= m_fSpeed;
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
		m_tInfo.fX += m_fSpeed;


	// Limit Player Pos in MapSize
	if (MAPSIZE_LEFT >= m_tInfo.fX)
		m_tInfo.fX = MAPSIZE_LEFT;
	else if (MAPSIZE_RIGHT <= m_tInfo.fX)
		m_tInfo.fX = MAPSIZE_RIGHT;
}

void CPlayer::OnCollision(DIRECTION eDir, CObj* other)
{
	switch (eDir)
	{
	case DIR_UP:
		if (other->CompareTag("Monster") || other->CompareTag("Turtle"))
		{
			m_fJumpPower *= 0.9f;
			m_fGTime = 0.f;
			m_fGravity = 9.8f;
		}
		else
		{
			m_bOnBlock = true;
			m_bJump = false;
			m_fGravity = 9.8f;
		}
		break;
	case DIR_DOWN:
		m_fJumpPower = 0.f;
		break;
	case DIR_LEFT:
		if (other->CompareTag("Monster") || other->CompareTag("Turtle"))
		{
			if (m_bUnbtb)
				break;

			m_bUnbtb = true;
			m_fOldTime = GetTickCount64();
			DownLife();
			if (m_Sprite == IDB_SUPERMARIO)
			{
				m_Sprite = IDB_SMALLMARIO;
			}
		}
		break;
	case DIR_RIGHT:
		if (other->CompareTag("Monster") || other->CompareTag("Turtle"))
		{
			if (m_bUnbtb)
				break;

			m_bUnbtb = true;
			m_fOldTime = GetTickCount64();
			DownLife();
			if (m_Sprite == IDB_SUPERMARIO)
			{
				m_Sprite = IDB_SMALLMARIO;
			}
		}
		break;
	default:
		break;
	}
}

void CPlayer::UpGradeBody()
{
	m_tInfo.fCX += 1.0; m_tInfo.fCY += 1.0;
	m_Sprite = IDB_SUPERMARIO;
	m_bUnbtb = false;
}

void CPlayer::UpLife()
{
	++m_fLifeCount;
	UpGradeBody();
	CUIMgr::Get_Instance()->SetLifeCount(m_fLifeCount);

	if (0 >= m_fLifeCount)
	{
		Set_Dead();
		return;
	}
}

void CPlayer::DownLife()
{
	--m_fLifeCount;
	CUIMgr::Get_Instance()->SetLifeCount(m_fLifeCount);

	if (0 >= m_fLifeCount)
	{
		Set_Dead();
		return;
	}
}


void CPlayer::Release(void)
{
	//m_pRelexBullet = nullptr;
}
