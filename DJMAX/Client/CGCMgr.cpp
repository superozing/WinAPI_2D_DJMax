#include "pch.h"
#include "CGCMgr.h"

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
		// Entity�� �̹� �������� �ʾҴ°�
		if (nullptr != m_Entity[i])
		{
			delete m_Entity[i];
		}
	}
}
