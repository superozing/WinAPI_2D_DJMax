#pragma once
#include "CObj.h"

class CTexture;

class CBackground
	:public CObj
{
	GENERATED_OBJECT(CObj);
private:
	CTexture*		m_bg;
	BLENDFUNCTION	m_blendFunc;

	float			m_fBlendAlpha;
	int				m_iAlphaDiff;
private:
	virtual void tick(float _DT) override;
	virtual void render(HDC _dc) override;

public:
	void SetTexture(CTexture* _backgroundTex) { m_bg = _backgroundTex; }

	void SmoothChangeAlpha(int _diff) { m_iAlphaDiff = _diff; }

public:
	CLONE(CBackground);
	CBackground();
	CBackground(const CBackground& _Origin);
	~CBackground();

};

