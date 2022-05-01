#pragma once

#include "Include.h"

class CMainGame
{
public:
	CMainGame();
	~CMainGame();

public:
	void Initialize(void);		// �����͸� �ʱ�ȭ�ϴ� �Լ�
	void Update(void);			// �� �����Ӹ��� �����ϴ� �Լ�
	void Late_Update(void);
	void Render(void);			// �� �����Ӹ��� ����ϴ� �Լ�
	void Release(void);			// ��ü �ı� �� �޸� ���� �Լ�


public:
	static float m_fTime;
private:
	HDC				m_hDC;

	TCHAR		m_szFPS[64];			// ��Ƽ ����Ʈ ��ݿ����� CHAR�� ���� �ڵ� ��ݿ����� �����ڵ�� ó�����ִ� ��ũ��
	int			m_iFPS;
	DWORD		m_dwTime;
	
};
