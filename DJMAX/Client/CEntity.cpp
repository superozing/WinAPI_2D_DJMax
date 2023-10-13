#include "pch.h"
#include "CEntity.h"

UINT_PTR CEntity::g_NextID = 0;

CEntity::CEntity()
	:m_ID(g_NextID++)
	,m_bDead(false)
{
}

// 복사 생성의 경우에도 id 값은 달라져야 한다
CEntity::CEntity(const CEntity& _other) 
	:m_ID(g_NextID++)
	,m_bDead(false)
{
}

CEntity::~CEntity()
{
}
