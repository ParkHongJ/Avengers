#include "stdafx.h"
#include "CollisionMgr.h"

CollisionMgr::CollisionMgr()
{
}


CollisionMgr::~CollisionMgr()
{
}


void CollisionMgr::Collision_Rect(list<CObj*> _Dest, list<CObj*> _Sour)
{
	RECT		rc{};

	for (auto& Dest : _Dest)
	{
		for (auto& Sour : _Sour)
		{
			if (IntersectRect(&rc, &(Dest->Get_Rect()), &(Sour->Get_Rect())))
			{
				Dest->OnCollision();
				Sour->OnCollision();
			}
		}
	}
}
// �����Ǿ� �ִ� ��ü  // �����̴� ��ü		
void CollisionMgr::Collision_RectEx(list<CObj*> _Dest, list<CObj*> _Sour)
{
	for (auto& Dest : _Dest)
	{
		for (auto& Sour : _Sour)
		{
			float	fX = 0.f, fY = 0.f;

			if (Check_Rect(Dest, Sour, &fX, &fY))
			{
				// ���� �浹
				if (fX > fY)
				{
					// �� �浹
					if (Dest->Get_Info().fY > Sour->Get_Info().fY)
					{
						Sour->Set_PosY(-fY);
						Dest->OnCollision(DIR_UP);
						Sour->OnCollision(DIR_UP);
					}

					else // �� �浹
					{
						Sour->Set_PosY(fY);
						Dest->OnCollision(DIR_DOWN);
						Sour->OnCollision(DIR_DOWN);
					}
				}
				// �¿� �浹
				else
				{
					// �� �浹
					if (Dest->Get_Info().fX > Sour->Get_Info().fX)
					{
						Sour->Set_PosX(-fX);
						Dest->OnCollision(DIR_LEFT);
						Sour->OnCollision(DIR_LEFT);
					}


					// �� �浹
					else
					{
						Sour->Set_PosX(fX);
						Dest->OnCollision(DIR_RIGHT);
						Sour->OnCollision(DIR_RIGHT);
					}

				}

			}
		}
	}
}

bool CollisionMgr::Check_Rect(CObj* pDest, CObj* pSour, float* pX, float* pY)
{
	float		fWidth = abs(pDest->Get_Info().fX - pSour->Get_Info().fX);
	float		fHeight = abs(pDest->Get_Info().fY - pSour->Get_Info().fY);

	float		fCX = (pDest->Get_Info().fCX + pSour->Get_Info().fCX) * 0.5f;
	float		fCY = (pDest->Get_Info().fCY + pSour->Get_Info().fCY) * 0.5f;

	if ((fCX > fWidth) && (fCY > fHeight))
	{
		*pX = fCX - fWidth;
		*pY = fCY - fHeight;

		return true;
	}

	return false;
}

bool CollisionMgr::Check_Sphere(CObj* pDest, CObj* pSour)
{
	// abs : ���밪�� �����ִ� �Լ�
	float	fWidth = (float)fabs((double)pDest->Get_Info().fX - pSour->Get_Info().fX);
	float	fHeight = (float)fabs((double)pDest->Get_Info().fY - pSour->Get_Info().fY);

	// sqrt : ��Ʈ�� �����ִ� �Լ�
	float	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

	float	fRadius = (pDest->Get_Info().fCX + pSour->Get_Info().fCX) * 0.5f;

	return fRadius > fDiagonal;
}

void CollisionMgr::Collision_Sphere(list<CObj*> _Dest, list<CObj*> _Sour)
{
	for (auto& Dest : _Dest)
	{
		for (auto& Sour : _Sour)
		{
			if (Check_Sphere(Dest, Sour))
			{
				Dest->OnCollision();
				Sour->OnCollision();
			}
		}
	}
}

