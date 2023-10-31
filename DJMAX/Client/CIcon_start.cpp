#include "pch.h"
#include "CIcon_start.h"
#include "CTimeMgr.h"

CIcon_start::CIcon_start()
	:m_fMoveUp(0.f)
{
}

CIcon_start::~CIcon_start()
{
}

void CIcon_start::tick(float _DT)
{
	CIcon::tick(_DT);

	if (m_fMoveUp != 0.f)
	{
		Vec2 vPos = CObj::GetPos();
		if (vPos.y - (m_fMoveUp * DT) <= -1800.f)
		{
			vPos.y = -1800.f;
			m_fMoveUp = 0.f;
		}
		else
		{
			vPos.y -= m_fMoveUp * DT;
		}
		CObj::SetPos(vPos);
	}
}
