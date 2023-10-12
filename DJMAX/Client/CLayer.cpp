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

void CLayer::tick()
{
	for (size_t i = 0; i < m_vecObjects.size(); ++i)
	{
		m_vecObjects[i]->tick();
	}
}

void CLayer::finaltick()
{
	for (size_t i = 0; i < m_vecObjects.size(); ++i)
	{
		m_vecObjects[i]->finaltick();
	}
}

void CLayer::render(HDC _dc)
{
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
