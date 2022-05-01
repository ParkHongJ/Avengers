#pragma once

#include "Include.h"

class CMapEditor
{
public:
	CMapEditor();
	~CMapEditor();

public:
	static		CMapEditor* Get_Instance(void)
	{
		if (!m_pInstance)
		{
			m_pInstance = new CMapEditor;
		}

		return m_pInstance;
	}

	static	void	Destroy_Instance(void)
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

public:
	void	Update_GetKey();
	void	Edit_CreateBlock();
	void	Edit_DeleteBlock();
	void	CreateBlock(BLOCKID eId, float fX, float fY);

	void	Save();
	void	Load();
	void    CreateAllBlockInList();

public:
	void	Initialize();
	void	Update(void);
	void	Render(HDC hDC);
	void	Release();

private:
	static CMapEditor* m_pInstance;

private:
	list<BlockInfo>		m_BlockList;
	BLOCKID				m_eCurBlockID;
	POINT				m_sMousePos;
	POINT				m_sCurBlockPos;

};
