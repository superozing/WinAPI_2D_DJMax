#include "pch.h"
#include "CBackground_alpha.h"

#include "CTimeMgr.h"

#define ALPHA_CHANGE_SPEED 150 * minus

void CBackground_alpha::tick(float _DT)
{
	static int minus = 1;
	m_acc += DT;
	if (m_acc > 2.f)
	{
		m_acc = 0.f;
		CBackground::SmoothChangeAlpha(ALPHA_CHANGE_SPEED);
		minus *= -1;

	}
	CBackground::tick(_DT);
}

CBackground_alpha::CBackground_alpha()
	:m_acc(0.f)
{
}

CBackground_alpha::~CBackground_alpha()
{
}
