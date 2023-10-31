#pragma once
#include "CObj.h"

class CTexture;

class CIcon :
    public CObj
{
	GENERATED_OBJECT(CObj);
protected:
	CTexture*		m_pIcon;
	BLENDFUNCTION	m_blendFunc;
	float			m_fBlendAlpha;
	int				m_iAlphaDiff;

public:	
	virtual void tick(float _DT);
	virtual void render(HDC _dc);

	void SmoothChangeAlpha(int _diff) { m_iAlphaDiff = _diff; }
	void SetIcon(CTexture* _IconImg) { m_pIcon = _IconImg; }
public:
	CLONE(CIcon);
	CIcon();
	~CIcon();
};

