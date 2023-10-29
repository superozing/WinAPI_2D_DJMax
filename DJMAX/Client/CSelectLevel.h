#pragma once
#include "CLevel.h"
class CSelectLevel :
    public CLevel
{
private:
	virtual void init() override;
	virtual void enter() override;
	virtual void exit() override;
	virtual void tick() override;
};

