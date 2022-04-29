#pragma once

#include "Include.h"

class CLine
{
public:
	CLine();
	CLine(LINE tLine);
	CLine(LINEPOINT& tLeft, LINEPOINT& tRight);
	~CLine();

public:
	const LADDER& Get_Info(void) const { return m_tInfo;}

public:
	void	Render(HDC hDC);

private:
	LADDER m_tInfo;
};

