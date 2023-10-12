#include "pch.h"
#include "manager.h"
#include "CLevelMgr.h"
#include "CTimeMgr.h"

void Manager::Init()
{
	CTimeMgr::GetInst()->init();

}

void Manager::UpdateTick()
{
	// Delta Time
	CTimeMgr::GetInst()->tick();

	// Key state

	// Camera

}

void Manager::LevelTick()
{
	// Level Tick
	
	// Collision Tick

}

void Manager::LevelRender(/*HDC _dc*/)
{
	// Level Render

}

void Manager::TaskTick()
{
	// Task Execute

	// GC

}
