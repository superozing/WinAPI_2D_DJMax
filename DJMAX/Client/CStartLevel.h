#pragma once
#include "CLevel.h"
class CStartLevel :
    public CLevel
{
	virtual void init() override;
	virtual void enter() override;
	virtual void exit() override;
	virtual void tick() override;
};
