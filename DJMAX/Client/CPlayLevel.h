#pragma once
#include "CLevel.h"
class CPlayLevel :
    public CLevel
{
	virtual void init() override;
	virtual void enter() override;
	virtual void exit() override;
};

