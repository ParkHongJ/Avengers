#include "stdafx.h"
#include "Player.h"
#include "AbstractFactory.h"
#include "Shield.h"
#include "ScrewBullet.h"
#include "GuideBullet.h"
#include "ObjMgr.h"
#include "LineMgr.h"
#include <math.h>
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

	// ������ ����
	Key_Input();

	tempLineL.x += m_tempSpeed;
	tempLineR.x += m_tempSpeed;

	// ��� ������ ���� �ڿ� �������� ��ǥ�� �ϼ�
	Update_Rect();

	return OBJ_NOEVENT;
}

void CPlayer::Late_Update(void)
{
	m_tPosin.x = long(m_tInfo.fX + m_fDiagonal * cosf((m_fAngle * PI) / 180.f));
	m_tPosin.y = long(m_tInfo.fY - m_fDiagonal * sinf((m_fAngle * PI) / 180.f));

	if (100 >= tempLineL.x || WINCX - 100 <= tempLineR.x)
		m_tempSpeed *= -1.f;
}


void CPlayer::Release(void)
{

}

void CPlayer::OnTriggerStay(CObj* other)
{
	if (other->CompareTag("Moveable"))
	{

	}
}

void CPlayer::Key_Input(void)
{
	float	fY = 0.f;

	if (CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, &fY))
	{

		m_tInfo.fY = fY - m_tInfo.fCY * 0.5f;
	}
	// GetKeyState
	if (GetAsyncKeyState(VK_LEFT))
	{
		m_tInfo.fX -= m_fSpeed;

		
	}

	if (GetAsyncKeyState(VK_RIGHT))
	{
		m_tInfo.fX += m_fSpeed;

		
	}
	if (GetAsyncKeyState(VK_SPACE) && !m_bJump)
	{
			m_bJump = true;
	}
	//if (m_bJump)
	//{

	//	static float time = 1.f;
	//		// x = speed * cos(����) * �ð�
	//		// y = speed * sin(����) * �ð� - 1/	2 * 9.8 * (�ð� * �ð�)
	//		// x = sqrt(x*x + y*y) * cos(m_fAngle * PI / 180)	
	//		// (���� ���� ����)�� �̿��Ͽ� ������ �����϶�
	//		// Y = �ӵ� * sin(����) * �ð� - 1/2(�߷°��(9.8) * �ð� * �ð�)
	//		m_fAngle = 75.f; 
	//		//time += 0.01f;
	//		m_tInfo.fX += 8.f * cosf((m_fAngle * PI) / 180.f) * time;
	//		m_tInfo.fY -= 8.f * sinf((m_fAngle * PI) / 180.f) * time - (0.5f * 9.8f * (time * time));

	//		

	//		time += 0.006f;
	//}
	if (GetAsyncKeyState(VK_UP))
		m_tInfo.fY -= m_fSpeed;

	if (GetAsyncKeyState(VK_DOWN))
		m_tInfo.fY += m_fSpeed;


}

template<typename T>
CObj* CPlayer::Create_Bullet(void)
{
	CObj* pBullet = CAbstractFactory<T>::Create((float)m_tPosin.x, (float)m_tPosin.y, m_fAngle);

	return pBullet;
}

CObj* CPlayer::Create_Shield(void)
{
	CObj* pShield = CAbstractFactory<CShield>::Create();
	pShield->Set_Target(this);

	return pShield;
}

void CPlayer::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	// ���� �׸���
	MoveToEx(hDC, (int)m_tInfo.fX, (int)m_tInfo.fY, nullptr);
	LineTo(hDC, (int)m_tPosin.x, (int)m_tPosin.y);
	MoveToEx(hDC, tempLineL.x, tempLineL.y, nullptr);
	LineTo(hDC, tempLineR.x, tempLineR.y);
}
void CPlayer::Jump(void)
{

}