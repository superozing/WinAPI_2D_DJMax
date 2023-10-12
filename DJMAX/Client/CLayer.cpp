#include "pch.h"
#include "CLayer.h"

#include "CObj.h"


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

	for (; iter != m_vecObjects.end();)
	{
		if ((*iter)->IsDead())
		{
			//CGCMgr::GetInst()->AddEntity((*iter));
			iter = m_vecObjects.erase(iter);
		}
		else
		{
			(*iter)->render(_dc);
			++iter;
		}
	}
}

void CLayer::DeleteAllObjects()
{
	for (size_t i = 0; i < m_vecObjects.size(); ++i)
	{
		delete m_vecObjects[i];
	}

	m_vecObjects.clear();
}

CLayer::CLayer()
{
}

CLayer::~CLayer()
{
	DeleteAllObjects();

}
