#pragma once
#include "CLevel.h"

class CGear_PlayLevel;

class CPlayLevel :
    public CLevel
{
private:
	CGear_PlayLevel* m_pGear;
public:


	virtual void init() override;
	virtual void enter() override;
	virtual void exit() override;
	virtual void tick() override;

};

