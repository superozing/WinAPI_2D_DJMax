#pragma once
#include "CObj.h"

class CTestObj
	: public CObj
{
	GENERATED_OBJECT(CObj);
private:

public:
	virtual void tick(float _DT) override;
	virtual void render(HDC _dc) override;

public:
	CTestObj();
	~CTestObj();
};

