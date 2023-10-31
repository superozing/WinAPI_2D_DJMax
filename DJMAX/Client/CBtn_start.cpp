#include "pch.h"
#include "CBtn_start.h"
#include "CTimeMgr.h"

CBtn_start::CBtn_start()
	:m_fMoveUp(0.f)
{
}

CBtn_start::~CBtn_start()
{
}

void CBtn_start::tick(float _DT)
{
	CBtnUI::tick(_DT);

	if (m_fMoveUp != 0.f)
	{
		Vec2 vPos = CObj::GetPos();
		if (vPos.y - (m_fMoveUp * DT) <= 220.f)
		{
			vPos.y = 220.f;
			m_fMoveUp = 0.f;
		}
		else
		{
			vPos.y -= m_fMoveUp * DT;
		}
		CObj::SetPos(vPos);
	}
}

