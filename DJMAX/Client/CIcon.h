#pragma once
#include "CObj.h"

class CTexture;

class CIcon :
    public CObj
{
private:
	CTexture* m_pIcon;
	BLENDFUNCTION	m_blendFunc;

public:	
	virtual void tick(float _DT);
	virtual void render(HDC _dc);

public:
	
};

