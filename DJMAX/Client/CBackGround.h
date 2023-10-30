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
	void SetTexture(CTexture* _backgroundTex) { m_bg = _backgroundTex; }

public:
	CLONE(CBackGround);
	CBackGround();
	CBackGround(const CBackGround& _Origin);
	~CBackGround();

};

