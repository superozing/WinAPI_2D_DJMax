#include "pch.h"
#include "CLayer.h"

#include "CObj.h"

#include "CGCMgr.h"

CLayer::CLayer()
{
}

CLayer::~CLayer()
{
	DeleteAllObjects();
}

void CLayer::begin()
{
	for (size_t i = 0; i < m_vecObjects.size(); ++i)
	{
		m_vecObjects[i]->begin();
	}
}

void CLayer::tick(float _DT)
{
	for (size_t i = 0; i < m_vecObjects.size(); ++i)
	{
		m_vecObjects[i]->tick(_DT);
	}
}

void CLayer::finaltick(float _DT)
{
	for (size_t i = 0; i < m_vecObjects.size(); ++i)
	{
		m_vecObjects[i]->finaltick(_DT);
	}
}

void CLayer::render(HDC _dc)
{
	vector<CObj*>::iterator iter = m_vecObjects.begin();

	// 레이어의 모든 오브젝트를 순회할 때, 순회하는 김에 동시에 레이어에 Dead 상태인 오브젝트가 있다면
	// 그 오브젝트를 GC에 넘기고 벡터에서 지워버린다.
	for (; iter != m_vecObjects.end();)
	{
		if ((*iter)->IsDead())
		{
			CGCMgr::GetInst()->AddEntity((*iter));
			iter = m_vecObjects.erase(iter);
		}
		else
		{
			(*iter)->render(_dc);
			++iter;
		}
	}
}

// CLevel::DeleteAllObjects()에 의해 동작됨.
void CLayer::DeleteAllObjects()
{
	for (size_t i = 0; i < m_vecObjects.size(); ++i)
	{
		delete m_vecObjects[i];
	}

	m_vecObjects.clear();
}

