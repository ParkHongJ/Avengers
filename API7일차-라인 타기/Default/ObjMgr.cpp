#include "stdafx.h"
#include "ObjMgr.h"
#include "CollisionMgr.h"
#include "UIMgr.h"
#include "SceneMgr.h"

CObjMgr* CObjMgr::m_pInstance = nullptr;

CObjMgr::CObjMgr()
{
}


CObjMgr::~CObjMgr()
{
	Release();
}

CObj* CObjMgr::Get_Target(OBJID eID, CObj* pObj)
{
	if (m_ObjList[eID].empty())
		return nullptr;

	CObj* pTarget = nullptr;
	float		fDistance = 0.f;

	for (auto& iter : m_ObjList[eID])
	{
		if (iter->Get_Dead())
			continue;

		float	fWidth = abs(pObj->Get_Info().fX - iter->Get_Info().fX);
		float	fHeight = abs(pObj->Get_Info().fY - iter->Get_Info().fY);

		float	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

		if ((!pTarget) || (fDistance > fDiagonal))
		{
			pTarget = iter;
			fDistance = fDiagonal;
		}
	}

	return pTarget;
}

void CObjMgr::Add_Object(OBJID eID, CObj* pObj)
{
	if ((eID >= OBJ_END) || (nullptr == pObj))
		return;

	m_ObjList[eID].push_back(pObj);
}

int CObjMgr::Update(void)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto iter = m_ObjList[i].begin();
			iter != m_ObjList[i].end(); )
		{
			int iResult = (*iter)->Update();

			if (OBJ_DEAD == iResult)
			{
				Safe_Delete<CObj*>(*iter);
				iter = m_ObjList[i].erase(iter);
			}
			else
				++iter;
		}
	}

	if (m_ObjList[OBJ_PLAYER].empty())
	{
		if(CSceneMgr::Get_Instance()->GetCurScene() != SCENE_EDIT)
			CSceneMgr::Get_Instance()->ChangeScene(SCENEID::SCENE_START);
		return 0;
	}
	if (2650.f < Get_Player()->Get_Info().fX && CSceneMgr::Get_Instance()->GetCurScene() != SCENE_BOSS)
	{
		CSceneMgr::Get_Instance()->ChangeScene(SCENEID::SCENE_BOSS);
		return OBJ_NOEVENT;
	}

	return 0;
}

void CObjMgr::Late_Update(void)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter : m_ObjList[i])
			iter->Late_Update();
	}


	CollisionMgr::Collision_RectEx(m_ObjList[OBJ_BLOCK], m_ObjList[OBJ_PLAYER]);
	CollisionMgr::Collision_RectEx(m_ObjList[OBJ_BLOCK], m_ObjList[OBJ_BULLET]); // 반사총알 벽 충돌
	CollisionMgr::Collision_RectEx(m_ObjList[OBJ_MOVINGBLOCK], m_ObjList[OBJ_BULLET]);
	CollisionMgr::Collision_RectEx(m_ObjList[OBJ_MOUSE], m_ObjList[OBJ_BLOCK], false);  // 에디터 마우스 블럭 충돌
	CollisionMgr::Collision_RectEx(m_ObjList[OBJ_MOUSE], m_ObjList[OBJ_MOVINGBLOCK], false);  // 에디터 마우스 블럭 충돌
	CollisionMgr::Collision_RectEx(m_ObjList[OBJ_MOUSE], m_ObjList[OBJ_TEMP], false);  // 에디터 마우스 몬스터 충돌
	CollisionMgr::Collision_RectEx(m_ObjList[OBJ_MOUSE], m_ObjList[OBJ_COIN], false);  // 에디터 마우스 몬스터 충돌

	CollisionMgr::Collision_RectEx(m_ObjList[OBJ_MOVINGBLOCK], m_ObjList[OBJ_PLAYER], false);
	
	CollisionMgr::Collision_Rect(m_ObjList[OBJ_COIN], m_ObjList[OBJ_PLAYER]);
	CollisionMgr::Collision_Rect(m_ObjList[OBJ_MUSHROOM], m_ObjList[OBJ_PLAYER]);
	// 코인과 플레이어의 충돌 체크 추가했어요 -민성-


	CollisionMgr::Collision_RectEx(m_ObjList[OBJ_BLOCK], m_ObjList[OBJ_TEMP]);
	CollisionMgr::Collision_RectEx(m_ObjList[OBJ_TEMP], m_ObjList[OBJ_PLAYER], false);	// Player Monster
	//=====================임시방편임============================================
	CollisionMgr::Collision_RectEx(m_ObjList[OBJ_TURTLE], m_ObjList[OBJ_TEMP]);
	CollisionMgr::Collision_RectEx(m_ObjList[OBJ_BLOCK], m_ObjList[OBJ_TURTLE]);
	CollisionMgr::Collision_RectEx(m_ObjList[OBJ_TURTLE], m_ObjList[OBJ_PLAYER]);
	//==========================================================================
	CollisionMgr::Collision_RectEx(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_BULLET]); // 반사총알 벽 충돌

}

void CObjMgr::Render(HDC hDC)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter : m_ObjList[i])
			iter->Render(hDC);
	}
}

void CObjMgr::Release(void)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter : m_ObjList[i])
			Safe_Delete<CObj*>(iter);

		m_ObjList[i].clear();
		
	}
}