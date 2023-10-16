#include "pch.h"
#include "CLevel.h"
#include "CTimeMgr.h"

#include "CObj.h"

void CLevel::begin()
{
	for (UINT i = 0; i < LAYER::END; ++i)
	{
		m_Layer[i]->begin();
	}
}

void CLevel::tick()
{

	for (UINT i = 0; i < LAYER::END; ++i)
	{
		m_Layer[i]->clear();
	}
	for (UINT i = 0; i < LAYER::END; ++i)
	{
		m_Layer[i]->tick(DT);
	}

	for (UINT i = 0; i < LAYER::END; ++i)
	{
		m_Layer[i]->finaltick(DT);
	}
}

void CLevel::render(HDC _dc)
{
	for (UINT i = 0; i < LAYER::END; ++i)
	{
		m_Layer[i]->render(_dc);
	}
}

void CLevel::AddObject(LAYER _LayerType, CObj* _Object)
{
	// ���̾ ������Ʈ�� ����ִ´�.
	m_Layer[_LayerType]->AddObject(_Object);

	// ���̾� �ε������� ������Ʈ�� �������ش�(������Ʈ�� �ڽ��� �Ҽӵ� ���̾� �ε����� �˰� �Ѵ�)
	_Object->m_iLayerIdx = _LayerType;
}

void CLevel::DeleteAllObjects()
{
	// ��� ���̾��� ������Ʈ ����
	for (UINT i = 0; i < LAYER::END; ++i)
	{
		m_Layer[i]->DeleteAllObjects();
	}
}

CLevel::CLevel()
	// :
{
	for (UINT i = 0; i < LAYER::END; ++i)
	{
		m_Layer[i] = new CLayer;
	}
}

CLevel::~CLevel()
{
	for (UINT i = 0; i < LAYER::END; ++i)
	{
		if (nullptr != m_Layer[i])
			delete m_Layer[i];
	}
}
