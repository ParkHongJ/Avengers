#include "stdafx.h"
#include "GameMgr.h"
#include "UIMgr.h"

CGameMgr* CGameMgr::m_pInstance = nullptr;

CGameMgr::CGameMgr() : time(1), m_iScore(0)
{
}

CGameMgr::~CGameMgr()
{
}

void CGameMgr::PlusScore()
{
	++m_iScore;
	CUIMgr::Get_Instance()->SetScore(m_iScore);
}

void CGameMgr::Release()
{
	m_iScore = 0;
	time = 0;

}
