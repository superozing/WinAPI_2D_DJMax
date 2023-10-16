#include "pch.h"
#include "CObj.h"

void CObj::tick(float _DT)
{
	for (size_t i = 0; i < m_vecComponent.size(); ++i)
	{
		m_vecComponent[i]->tick(_DT);
	}
}

void CObj::finaltick(float _DT)
{
	for (size_t i = 0; i < m_vecComponent.size(); ++i)
	{
		m_vecComponent[i]->finaltick(_DT);
	}
}

void CObj::render(HDC _dc)
{
	for (size_t i = 0; i < m_vecComponent.size(); ++i)
	{
		m_vecComponent[i]->render(_dc);
	}


	// 디버그 렌더
	//if (!DEBUG_RENDER)
	//	return;

	//SELECT_PEN(_dc, RED_PEN);

	//Vec2 vRenderPos = GetRenderPos();
	//MoveToEx(_dc, int(vRenderPos.x - 7.f), (int)vRenderPos.y, nullptr);
	//LineTo(_dc, int(vRenderPos.x + 7.f), (int)vRenderPos.y);

	//MoveToEx(_dc, int(vRenderPos.x), int(vRenderPos.y - 7.f), nullptr);
	//LineTo(_dc, int(vRenderPos.x), int(vRenderPos.y + 7.f));

}


void CObj::SetDead()
{
	m_bDead = true;

	for (size_t i = 0; i < m_vecComponent.size(); ++i)
	{
		m_vecComponent[i]->m_bDead = true;
	}
}

CObj::CObj()
	:m_iLayerIdx(-1)
{
}

CObj::~CObj()
{
	// 자신이 소멸될 때, 자신의 모든 컴포넌트도 소멸 시킴.
	
	for (size_t i = 0; i < m_vecComponent.size(); ++i)
	{
		if (nullptr != m_vecComponent[i])
			delete m_vecComponent[i];
	}
	
}
