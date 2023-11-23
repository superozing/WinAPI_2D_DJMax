#pragma once
#include "CObj.h"

class CAnimator;

class CEffectAnim 
	: public CObj
{
private:
	CAnimator*	m_Animator;
	wstring		m_AnimName;

private:
	virtual void tick(float _DT) override;
	virtual void render(HDC _dc) override;

public:
	void playAnim();


public:
	CLONE_DISABLE(CEffectAnim);
	CEffectAnim(wstring _AnimName, CTexture* _Altas, Vec2 _vLeftTop, Vec2 _vCutSize, Vec2 _vOffset, float _Duration, int _MaxFrm);
	CEffectAnim(const CEffectAnim& _Origin) = delete;
	~CEffectAnim();
};

