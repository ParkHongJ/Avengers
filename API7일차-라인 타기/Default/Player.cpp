#include "stdafx.h"
#include "Player.h"
#include "AbstractFactory.h"
#include "Shield.h"
#include "ScrewBullet.h"
#include "GuideBullet.h"
#include "ObjMgr.h"
#include "LineMgr.h"

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

	m_tInfo.fCX = 100.f;
	m_tInfo.fCY = 100.f;

	m_fSpeed = 10.f;

	m_fDiagonal = 100.f;
}

int CPlayer::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	// 연산을 진행
	Key_Input();



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
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	// 포신 그리기
	MoveToEx(hDC, (int)m_tInfo.fX, (int)m_tInfo.fY, nullptr);
	LineTo(hDC, (int)m_tPosin.x, (int)m_tPosin.y);
}

void CPlayer::Release(void)
{
	
}

void CPlayer::Key_Input(void)
{
	float	fY = 0.f;

	// GetKeyState
	if (GetAsyncKeyState(VK_LEFT))
	{
		m_tInfo.fX -= m_fSpeed;

		if (CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, &fY))
			m_tInfo.fY = fY;
	}

	if (GetAsyncKeyState(VK_RIGHT))
	{
		m_tInfo.fX += m_fSpeed;

		if (CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, &fY))
			m_tInfo.fY = fY;
	}


	if (GetAsyncKeyState(VK_UP))
		m_tInfo.fY -= m_fSpeed;

	if (GetAsyncKeyState(VK_DOWN))
		m_tInfo.fY += m_fSpeed;

	/*if (GetAsyncKeyState('W'))
		m_pBullet->push_back(Create_Bullet(DIR_UP));

	if (GetAsyncKeyState('A'))
		m_pBullet->push_back(Create_Bullet(DIR_LEFT));

	if (GetAsyncKeyState('S'))
		m_pBullet->push_back(Create_Bullet(DIR_DOWN));

	if (GetAsyncKeyState('D'))
		m_pBullet->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_RIGHT));*/


	/*if (GetAsyncKeyState(VK_LEFT))
	{
		if (GetAsyncKeyState(VK_DOWN))
		{
			m_tInfo.fX -= m_fSpeed / sqrtf(2.f);
			m_tInfo.fY += m_fSpeed / sqrtf(2.f);
		}
		else if (GetAsyncKeyState(VK_UP))
		{
			m_tInfo.fX -= m_fSpeed / sqrtf(2.f);
			m_tInfo.fY -= m_fSpeed / sqrtf(2.f);
		}

		else
			m_tInfo.fX -= m_fSpeed;
	}
	
	else if (GetAsyncKeyState(VK_RIGHT))
	{
		if (GetAsyncKeyState(VK_DOWN))
		{
			m_tInfo.fX += m_fSpeed / sqrtf(2.f);
			m_tInfo.fY += m_fSpeed / sqrtf(2.f);
		}
		else if (GetAsyncKeyState(VK_UP))
		{
			m_tInfo.fX += m_fSpeed / sqrtf(2.f);
			m_tInfo.fY -= m_fSpeed / sqrtf(2.f);
		}

		else
			m_tInfo.fX += m_fSpeed;
	}
		
	else if (GetAsyncKeyState(VK_UP))
		m_tInfo.fY -= m_fSpeed;

	else if (GetAsyncKeyState(VK_DOWN))
		m_tInfo.fY += m_fSpeed;*/

	/*if (GetAsyncKeyState(VK_LEFT))
		m_fAngle -= 5.f;

	if (GetAsyncKeyState(VK_RIGHT))
		m_fAngle += 5.f;
	
	if (GetAsyncKeyState(VK_UP))
	{
		m_tInfo.fX += m_fSpeed * cosf((m_fAngle * PI) / 180.f);
		m_tInfo.fY -= m_fSpeed * sinf((m_fAngle * PI) / 180.f);
	}

	if (GetAsyncKeyState(VK_DOWN))
	{
		m_tInfo.fX += -m_fSpeed * cosf((m_fAngle * PI) / 180.f);
		m_tInfo.fY -= -m_fSpeed * sinf((m_fAngle * PI) / 180.f);
	}

	if (GetAsyncKeyState(VK_SPACE))
		CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, CAbstractFactory<CGuideBullet>::Create((float)m_tPosin.x, (float)m_tPosin.y, m_fAngle));*/


}

template<typename T>
CObj* CPlayer::Create_Bullet(void)
{
	CObj*		pBullet = CAbstractFactory<T>::Create((float)m_tPosin.x, (float)m_tPosin.y, m_fAngle);

	return pBullet;
}

CObj* CPlayer::Create_Shield(void)
{
	CObj*		pShield = CAbstractFactory<CShield>::Create();
	pShield->Set_Target(this);

	return pShield;
}

