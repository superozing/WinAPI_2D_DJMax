#pragma once
#include "CLevel.h"

class CMusicInfo;
class CMusicSelectBar;
class CSpeedTexture;

class CSelectLevel :
    public CLevel
{
	CMusicInfo*			m_MusicInfo;
	CMusicSelectBar*	m_Bar;
	CSpeedTexture*		m_Speed;

private:
	virtual void init() override;
	virtual void enter() override;
	virtual void exit() override;
	virtual void tick() override;

};