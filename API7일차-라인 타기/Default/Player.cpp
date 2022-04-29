#include "stdafx.h"
#include "Player.h"
#include "AbstractFactory.h"
#include "Shield.h"
#include "ScrewBullet.h"
#include "GuideBullet.h"
#include "ObjMgr.h"
#include "LineMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
CPlayer::CPlayer()
{
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize(void)
{
	m_tInfo.fX = 100.f;
	m_tInfo.fY = 300.f;

	m_tInfo.fCX = 16.f;
	m_tInfo.fCY = 16.f;

	m_fSpeed = 3.f;
	
	m_fDiagonal = 100.f;

	m_bJump = false;
	m_fJumpPower = 15.f;
	m_fJumpTime = 0.f;
	m_bOnGrounded = false;
	m_bAbility = false;
	m_bDBJump = false;
	m_iJumpCount = 0;
	m_bDrawAbility = false;
	temp = 1;
	m_bOnAir = true;
}

int CPlayer::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	// 연산을 진행
	Key_Input();
	Jumping();
	
	OffSet();



	// 모든 연산이 끝난 뒤에 최종적인 좌표를 완성
	Update_Rect();

	return OBJ_NOEVENT;
}

void CPlayer::Late_Update(void)
{
	m_tPosin.x = long(m_tInfo.fX + m_fDiagonal * cosf((m_fAngle * PI) / 180.f));
	m_tPosin.y = long(m_tInfo.fY - m_fDiagonal * sinf((m_fAngle * PI) / 180.f));
}

void CPlayer::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top, m_tRect.right + iScrollX, m_tRect.bottom);

	// 포신 그리기
	MoveToEx(hDC, (int)m_tInfo.fX + iScrollX, (int)m_tInfo.fY, nullptr);
	LineTo(hDC, (int)m_tPosin.x + iScrollX, (int)m_tPosin.y);

	/*if (m_bAbility)
	{
		MoveToEx(hDC, (int)m_tInfo.fX + iScrollX, (int)m_tInfo.fY, nullptr);
		POINT mouse = {};
		GetCursorPos(&mouse);
		ScreenToClient(g_hWnd, &mouse);
		LineTo(hDC, (int)mouse.x, (int)mouse.y);
	}*/
	
}


void CPlayer::OnTriggerStay(CObj* other)
{
	
	m_bOnGrounded = true;
	//m_bOnAir = true;
	//tempP = other;

}

void CPlayer::Key_Input(void)
{
	float	fY = 0.f;

	// GetKeyState
	if (GetAsyncKeyState(VK_LEFT))
	{
		m_tInfo.fX -= m_fSpeed;
	}

	if (GetAsyncKeyState(VK_RIGHT))
	{
		m_tInfo.fX += m_fSpeed;
	}

	/*if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
	{
		m_tInfo.fCX = 25.f;
		m_tInfo.fCY = 25.f;
	}
	else
	{
		m_tInfo.fCX = 100.f;
		m_tInfo.fCY = 100.f;
	}*/

	if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE))
	{
		if (m_iJumpCount == 2)
			return; 


		m_bJump = true;
		m_bOnGrounded = false;
		if (m_bJump && m_fJumpTime > 0)
		{
			m_bDBJump = true;
			m_fJumpTime = 0.f;
		}
		m_iJumpCount++;
		/*temp = temp * -1;
		m_bJump = true;*/
		return;
	}
	if (CKeyMgr::Get_Instance()->Key_Down(VK_UP) && m_bAbility)
	{
		m_bDrawAbility = true;
	}
}
void CPlayer::Jumping(void)
{
	float		fY = 0.f;

	//bool		bLineCol = CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, &fY);
	//벽위에 올라타기 임시
	/*if (bLineCol && m_bOnGrounded && tempP)
	{
		m_tInfo.fY = tempP->Get_Info().fY - 70.f;
		m_tInfo.fY = fY;
		return;
	}*/
	if (m_bOnGrounded == true)
	{
		m_fJumpTime = 0.f;
		return;
	}
	//점프중이면
	if (m_bJump)
	{
		float fDBJumpPower = m_fJumpPower * 25.f;
		m_tInfo.fY -= m_fJumpPower * m_fJumpTime - 9.8f * m_fJumpTime * m_fJumpTime * 0.5f * temp;
		m_fJumpTime += 0.2f;

		if (m_bDBJump)
		{
			float fDBJumpPower = m_fJumpPower * 0.9f;
			m_tInfo.fY -= fDBJumpPower * m_fJumpTime - 9.8f * m_fJumpTime * m_fJumpTime * 0.5f;
			m_fJumpTime += 0.1f;
		}
		//점프가 끝나면
		if (tempP && m_bOnGrounded)
		{
			m_bJump = false;
			m_bDBJump = false;
			m_bOnGrounded = true;
			m_fJumpTime = 0.f;
			//m_tInfo.fY = fY;
			m_iJumpCount = 0;
		}
	}
	else if (m_bOnAir)
	{
		m_tInfo.fY -= -1 * 9.8f * m_fJumpTime * m_fJumpTime * 0.5f;
		m_fJumpTime += 0.1f;
	}
	
	/*else if (tempP)
	{
		m_tInfo.fY = fY;
	}*/
}


void CPlayer::OffSet(void)
{
	int		iOffSetX = WINCX >> 1;
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iItv = 300;


	if (iOffSetX - iItv > m_tInfo.fX + iScrollX)
		CScrollMgr::Get_Instance()->Set_ScrollX(m_fSpeed);

	if (iOffSetX + iItv < m_tInfo.fX + iScrollX)
		CScrollMgr::Get_Instance()->Set_ScrollX(-m_fSpeed);
}
void CPlayer::Release(void)
{

}
