#pragma once
#include "CLevel.h"

class CGear_PlayLevel;
class CJudgeTexture;
class CLineShine;


class CPlayLevel :
    public CLevel
{
private:
	CGear_PlayLevel*	m_pGear;
	CJudgeTexture*		m_JudgeTex;
	CLineShine*			m_LineTex;
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

