#pragma once

class CUIMgr
{
public:
	CUIMgr();
	~CUIMgr();

public:
	static		CUIMgr* Get_Instance(void)
	{
		if (!m_pInstance)
		{
			m_pInstance = new CUIMgr;
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
	void SetScore(int iScore) { m_iScore = iScore; }
	void SetLifeCount(int iLifeCount) { m_iLifeCount = iLifeCount; }

public:
	void	Initialize();
	void	Update(void);
	void	Render(HDC hDC);

public:
	void	CoinRender(HDC hDC);
	void	LifeCountRender(HDC hDC);

private:
	static CUIMgr* m_pInstance;

	POINT	m_pScorePos;
	POINT	m_pLifeCountPos;
	int		m_iScore;
	int		m_iLifeCount;
};

