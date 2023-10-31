#pragma once
#include "CLevel.h"

class CSound;
class CBackground;
class CIcon_start;
class CBtn_start;

class CStartLevel :
    public CLevel
{
public:
	CSound*			m_pBGM;
	CSound*			m_pEffect_swoosh;
	CSound*			m_pEffect_choice;

	CBackground*	m_pStripeBg;
	CIcon_start*	m_pMainIcon;
	CBtn_start*		m_pSelect;
	CBtn_start*		m_pEditor;
private:
	virtual void init() override;
	virtual void enter() override;
	virtual void exit() override;
	virtual void tick() override;
};

