#pragma once
#include "CObj.h"

class CTexture;

class CCircle
	: public CObj
{
private:
	CTexture* m_CircleTex;

private:
	virtual void tick(float _DT) override;
	virtual void render(HDC _dc) override;
public:
	CLONE_DISABLE(CCircle);
	CCircle();
	CCircle(const CCircle& _Origin) = delete;
	~CCircle();
};

