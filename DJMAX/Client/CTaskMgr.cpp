#include "pch.h"
#include "CTaskMgr.h"

#include "CLevelMgr.h"
#include "CLevel.h"
#include "CObj.h"
#include "CComponent.h"

CTaskMgr::CTaskMgr()
{

}

CTaskMgr::~CTaskMgr()
{

}

void CTaskMgr::tick()
{
	for (size_t i = 0; i < m_vecTask.size(); ++i)
	{
		switch (m_vecTask[i].Type)
		{
		case CREATE_OBJECT:
		{
			CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();
			// param 1: 레이어,  param 2: 오브젝트
			pCurLevel->AddObject((LAYER)m_vecTask[i].Param_1, (CObj*)m_vecTask[i].Param_2);
			((CObj*)m_vecTask[i].Param_2)->begin();
		}
			break;
		case DELETE_OBJECT:
		{

		}
			break;
		case LEVEL_CHANGE:
		{

		}
			break;
		}
	}
}
