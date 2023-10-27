#include "pch.h"
#include "func.h"
#include "struct.h"
#include "CEntity.h"
#include "CTaskMgr.h"
#include "define.h"
void ChangeLevel(LEVEL_TYPE _type)
{
	FTask task = {};
	task.Type = LEVEL_CHANGE;
	task.Param_1 = (INT_PTR)_type;
	CTaskMgr::GetInst()->AddTask(task);
}
