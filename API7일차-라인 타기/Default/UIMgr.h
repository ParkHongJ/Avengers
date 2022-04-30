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
	void	Initialize(void);
	void	Update(void);
	void	Render(void);

private:
	static CUIMgr* m_pInstance;

};

