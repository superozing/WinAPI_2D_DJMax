#pragma once


class CLevelMgr
{
SINGLETON(CLevelMgr);
private:
	// 현재 레벨
	class CLevel*	m_pCurLevel;
	CLevel*			m_arrLevels[(UINT)LEVEL_TYPE::END];

public:
	CLevel* GetCurLevel() { return m_pCurLevel; }

private:
	void ChangeLevel(LEVEL_TYPE _Type);

public:
	void init();
	void tick();
	void render(HDC _dc);

	//friend class CTaskMgr;
};

