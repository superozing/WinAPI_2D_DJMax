#pragma once
#include "CLevel.h"

class CGear_PlayLevel;
class CJudgeTexture;
class CLineShine;
class CCoolbomb;

class CCombo;
class CFever;

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

	vector<int>			m_vecJudge;

public:
	virtual void init() override;
	virtual void enter() override;
	virtual void exit() override;
	virtual void tick() override;

public:
	vector<int>& GetVecJudge() { return m_vecJudge; }




	friend class CGear_PlayLevel;
};

