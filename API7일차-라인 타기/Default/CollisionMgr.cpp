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
				Dest->OnCollision(Sour);
				Sour->OnCollision(Dest);
			}
		}
	}
}
// 고정되어 있는 물체  // 움직이는 물체		
void CollisionMgr::Collision_RectEx(list<CObj*> _Dest, list<CObj*> _Sour, bool _bIsPush)
{
	for (auto& Dest : _Dest)
	{
		for (auto& Sour : _Sour)
		{
			float	fX = 0.f, fY = 0.f;

			if (Check_Rect(Dest, Sour, &fX, &fY))
			{
				// 상하 충돌
				if (fX > fY)
				{
					// 상 충돌
					if (Dest->Get_Info().fY > Sour->Get_Info().fY)
					{
						if(_bIsPush) Sour->Set_PosY(-fY);
						Dest->OnCollision(DIR_UP,Sour);
						Sour->OnCollision(DIR_UP, Dest);
					}

					else // 하 충돌
					{
						if (_bIsPush) Sour->Set_PosY(fY);
						Dest->OnCollision(DIR_DOWN, Sour);
						Sour->OnCollision(DIR_DOWN, Dest);
					}
				}
				// 좌우 충돌
				else
				{
					// 좌 충돌
					if (Dest->Get_Info().fX > Sour->Get_Info().fX)
					{
						if (_bIsPush) Sour->Set_PosX(-fX);
						Dest->OnCollision(DIR_LEFT, Sour);
						Sour->OnCollision(DIR_LEFT, Dest);
					}


					// 우 충돌
					else
					{
						if (_bIsPush) Sour->Set_PosX(fX);
						Dest->OnCollision(DIR_RIGHT, Sour);
						Sour->OnCollision(DIR_RIGHT, Dest);
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
	// abs : 절대값을 구해주는 함수
	float	fWidth = (float)fabs((double)pDest->Get_Info().fX - pSour->Get_Info().fX);
	float	fHeight = (float)fabs((double)pDest->Get_Info().fY - pSour->Get_Info().fY);

	// sqrt : 루트를 씌워주는 함수
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

