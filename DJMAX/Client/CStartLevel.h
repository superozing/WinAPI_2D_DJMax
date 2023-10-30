#pragma once
#include "CLevel.h"

class CSound;
class CBackground;

class CStartLevel :
    public CLevel
{
public:
	CSound*			m_pBGM;
	CBackground*	m_pStripeBg;

private:
	virtual void init() override;
	virtual void enter() override;
	virtual void exit() override;
	virtual void tick() override;
};

