#pragma once
#include "CLevel.h"

class CGear;

class CPlayLevel :
    public CLevel
{
private:
	CGear* m_pGear;
public:


	virtual void init() override;
	virtual void enter() override;
	virtual void exit() override;
	virtual void tick() override;

};

