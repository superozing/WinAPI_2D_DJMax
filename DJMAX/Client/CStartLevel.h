#pragma once
#include "CLevel.h"

class CStartLevel :
    public CLevel
{
public:
	
private:
	virtual void init() override;
	virtual void enter() override;
	virtual void exit() override;
	virtual void tick() override;
};

