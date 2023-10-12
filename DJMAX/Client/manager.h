#pragma once

class Manager
{
public:
	static void Init();
	static void UpdateTick();
	static void LevelTick();
	static void LevelRender(HDC _dc);
	static void TaskTick();
};