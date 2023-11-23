#include "pch.h"
#include "CEffectAnim.h"
#include "CAnimator.h"

CEffectAnim::CEffectAnim(wstring _AnimName, CTexture* _Altas,
	Vec2 _vLeftTop, Vec2 _vCutSize, Vec2 _vOffset, float _Duration, int  _MaxFrm)
	:m_Animator(nullptr)
	, m_AnimName(_AnimName)
{
	m_Animator = AddComponent<CAnimator>(m_AnimName + L"_Animator");
	m_Animator->CreateAnimation(m_AnimName, _Altas, _vLeftTop, _vCutSize, _vOffset, _Duration, _MaxFrm);
}

CEffectAnim::~CEffectAnim()
{
}

void CEffectAnim::playAnim()
{
	m_Animator->Play(m_AnimName, false);
}

void CEffectAnim::tick(float _DT)
{
	CObj::tick(_DT);
}

void CEffectAnim::render(HDC _dc)
{
	CObj::render(_dc);
}

