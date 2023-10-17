#include "pch.h"
#include "manager.h"
#include "CLevelMgr.h"
#include "CTimeMgr.h"
#include "CPathMgr.h"
#include "CKeyMgr.h"


#include "CTaskMgr.h"
#include "CGCMgr.h"

#include "CCamera.h"

void Manager::Init()
{
	CTimeMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();
	CPathMgr::init();
	CLevelMgr::GetInst()->init();

}

void Manager::UpdateTick()
{
	// Delta Time
	CTimeMgr::GetInst()->tick();

	// Key state
	CKeyMgr::GetInst()->tick();

	// Camera
	CCamera::GetInst()->tick();

}

void Manager::LevelTick()
{
	// Level Tick
	CLevelMgr::GetInst()->tick();

	// Collision Tick

	// UI Tick

}

void Manager::LevelRender(HDC _dc)
{
	// Level Render
	CLevelMgr::GetInst()->render(_dc);
}

void Manager::TaskTick()
{
	// Task Execute
	CTaskMgr::GetInst()->tick();
	// GC
	CGCMgr::GetInst()->tick();

}
