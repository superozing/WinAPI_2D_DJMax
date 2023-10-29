#include "pch.h"
#include "CGCMgr.h"

#include "CEntity.h"


CGCMgr::CGCMgr()
{

}

CGCMgr::~CGCMgr()
{
	for (size_t i = 0; i < m_Entity.size(); ++i)
	{
		if (nullptr != m_Entity[i])
		{
			delete m_Entity[i];
		}
	}
}
void CGCMgr::tick()
{
	if (m_Entity.size() < GARBAGE_MAX_SIZE)
	{
		return;
	}
	for (size_t i = 0; i < m_Entity.size(); ++i)
	{
		// Entity가 이미 지워지지 않았는가
		if (nullptr != m_Entity[i])
		{
			delete m_Entity[i];
		}
	}

	m_Entity.clear();
}
