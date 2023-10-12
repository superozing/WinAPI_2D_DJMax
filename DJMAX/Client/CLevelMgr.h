#pragma once


class CLevelMgr
{
SINGLETON(CLevelMgr);
private:
	// ���� ����
	class CLevel*	m_pCurLevel;
	CLevel* m_arrLevels[];

public:
	CLevel* GetCurLevel() { return m_pCurLevel; }

public:
	void init();
	void tick();
	void render(HDC _dc);
};

