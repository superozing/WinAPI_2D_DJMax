#pragma once
#include "CLevel.h"

class CGear_PlayLevel;
class CJudgeTexture;
class CLineShine;
class CCoolbomb;
class CEffectAnim;

class CCombo;
class CFever;

struct MUSICINFO;

class CPlayLevel :
    public CLevel
{
private:
	CGear_PlayLevel*	m_pGear;
	CJudgeTexture*		m_JudgeTex;
	CLineShine*			m_LineTex;		// 판정 시 
	CCoolbomb*			m_CoolbombTex;	// 판정 시 coolbomb 출력

	CCombo*				m_Combo; // combo 수치 조절, render
	CFever*				m_Fever; // fever 수치 조절, render

	CEffectAnim*		m_FeverEffectArr[2];
	
	vector<int>			m_vecJudge;

	MUSICINFO*			m_CurMusicInfo;


public:
	virtual void init() override;
	virtual void enter() override;
	virtual void exit() override;
	virtual void tick() override;

public:
	vector<int>* GetVecJudge() { return &m_vecJudge; }
	MUSICINFO* GetCurMusicInfo() { return m_CurMusicInfo; }



	friend class CGear_PlayLevel;
};

