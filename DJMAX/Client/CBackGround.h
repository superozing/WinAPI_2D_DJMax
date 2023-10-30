#pragma once
#include "CObj.h"

class CTexture;

class CBackGround
	:public CObj
{
	GENERATED_OBJECT(CObj);
private:
	CTexture*		m_bg;
	BLENDFUNCTION	m_blendFunc;

private:
	virtual void render(HDC _dc) override;
public:
	CBackGround();
	~CBackGround();

};

