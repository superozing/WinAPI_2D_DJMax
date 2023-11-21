#pragma once
#include "CLevel.h"
class CMusicInfo;

class CSelectLevel :
    public CLevel
{
	CMusicInfo* m_MusicInfo;
private:
	virtual void init() override;
	virtual void enter() override;
	virtual void exit() override;
	virtual void tick() override;

};