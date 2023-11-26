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

	int				m_CulSpeed;
	int				m_CulMusicDifficult;

	int				m_ComboBuffer;
	int				m_BestCombo;


public:
	CLevel* GetCurLevel() { return m_pCurLevel; }

	MUSICINFO* GetCurMusicInfo() 
	{ 
		return m_CurMusicInfo; 
	}
	void SetCurMusicInfo(MUSICINFO* _CurMusicInfo) { m_CurMusicInfo = _CurMusicInfo; }
	
	void SetSpeed(int _speed) { m_CulSpeed = _speed; }
	int  GetSpeed() const { return m_CulSpeed; }

	void SetMusicDifficult(int _difficult) { m_CulMusicDifficult = _difficult; }
	int  GetMusicDifficult() const { return m_CulMusicDifficult; }

	void SetComboBuf(int _Combo) 
	{ 
		m_ComboBuffer = _Combo; 
		if (m_BestCombo < m_ComboBuffer)
		{
			m_BestCombo = m_ComboBuffer;
		}
	}
	int GetComboBuf() { return m_ComboBuffer; }
	int GetBestCombo() { return m_BestCombo; }
private:
	void ChangeLevel(LEVEL_TYPE _Type);

public:
	void init();
	void tick();
	void render(HDC _dc);

	friend class CTaskMgr;
};

