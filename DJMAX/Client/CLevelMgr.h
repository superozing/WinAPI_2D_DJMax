#pragma once

struct MUSICINFO;

class CLevelMgr
{
SINGLETON(CLevelMgr);
private:
	// 현재 레벨
	MUSICINFO*		m_CurMusicInfo;
	class CLevel*	m_pCurLevel;
	CLevel*			m_arrLevels[(UINT)LEVEL_TYPE::END];

public:
	CLevel* GetCurLevel() { return m_pCurLevel; }

	MUSICINFO* GetCurMusicInfo() 
	{ 
		return m_CurMusicInfo; 
	}
	void SetCurMusicInfo(MUSICINFO* _CurMusicInfo) { m_CurMusicInfo = _CurMusicInfo; }
private:
	void ChangeLevel(LEVEL_TYPE _Type);

public:
	void init();
	void tick();
	void render(HDC _dc);

	friend class CTaskMgr;
};

