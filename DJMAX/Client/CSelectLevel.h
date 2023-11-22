#pragma once
#include "CLevel.h"

class CMusicInfo;
class CMusicSelectBar;

class CSelectLevel :
    public CLevel
{
	CMusicInfo*			m_MusicInfo;
	CMusicSelectBar*	m_Bar;
private:
	virtual void init() override;
	virtual void enter() override;
	virtual void exit() override;
	virtual void tick() override;

};