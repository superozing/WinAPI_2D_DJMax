#include "pch.h"
#include "CObj.h"

#include "CEngine.h"
#include "CTaskMgr.h"

// 오브젝트를 상속 받는 모든 파생 오브젝트 들은, 반드시 부모 쪽 tick를 호출해주어야 함.
void CObj::tick(float _DT)
{
	for (size_t i = 0; i < m_vecComponent.size(); ++i)
	{
		m_vecComponent[i]->tick(_DT);
	}
}

// 오브젝트를 상속 받는 모든 파생 오브젝트 들은, 반드시 부모 쪽 finaltick를 호출해주어야 함.
void CObj::finaltick(float _DT)
{
	for (size_t i = 0; i < m_vecComponent.size(); ++i)
	{
		m_vecComponent[i]->finaltick(_DT);
	}
}

// 오브젝트를 상속 받는 모든 파생 오브젝트 들은, 반드시 부모 쪽 render를 호출해주어야 함.
void CObj::render(HDC _dc)
{
	for (size_t i = 0; i < m_vecComponent.size(); ++i)
	{
		m_vecComponent[i]->render(_dc);
	}


	// 디버그 렌더
	if (!DEBUG_RENDER)
		return;

	SELECT_PEN(_dc, RED_PEN);

	Vec2 vRenderPos = GetRenderPos();
	MoveToEx(_dc, int(vRenderPos.x - 7.f), (int)vRenderPos.y, nullptr);
	LineTo(_dc, int(vRenderPos.x + 7.f), (int)vRenderPos.y);

	MoveToEx(_dc, int(vRenderPos.x), int(vRenderPos.y - 7.f), nullptr);
	LineTo(_dc, int(vRenderPos.x), int(vRenderPos.y + 7.f));

}

void CObj::Destroy()
{
	FTask task;
	task.Type = TASK_TYPE::DELETE_OBJECT;
	task.Param_1 = (INT_PTR)this;

	CTaskMgr::GetInst()->AddTask(task);
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
