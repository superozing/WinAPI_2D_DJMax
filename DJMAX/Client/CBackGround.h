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
	int				m_iMaxAlpha;
protected:
	virtual void tick(float _DT) override;
	virtual void render(HDC _dc) override;

public:
	void SetTexture(CTexture* _backgroundTex) { m_bg = _backgroundTex; }
	void SetMaxAlpha(int _maxAlpha) { m_iMaxAlpha = _maxAlpha; }

	void SmoothChangeAlpha(int _diff) { m_iAlphaDiff = _diff; }
	void SetAlpha(BYTE _diff) { m_fBlendAlpha = (float)_diff; m_blendFunc.SourceConstantAlpha = _diff; }

public:
	CLONE(CBackground);
	CBackground();
	CBackground(const CBackground& _Origin);
	~CBackground();

};

