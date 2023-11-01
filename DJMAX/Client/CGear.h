#pragma once
#include "CObj.h"


class CNote;

class CGear :
    public CObj
{
	GENERATED_OBJECT(CObj);
public:
	vector<CNote*>	m_vecNotes;

private:
	virtual void tick(float _DT) override;
	virtual void render(HDC _dc) override;
};

