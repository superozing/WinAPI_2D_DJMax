#include "pch.h"
#include "CIcon.h"
#include "CTexture.h"
#include "CTimeMgr.h"
#include "CEngine.h"

void CIcon::tick(float _DT)
{
	Super::tick(_DT);
	BYTE& alpha = m_blendFunc.SourceConstantAlpha;

	if (m_iAlphaDiff != 0)
	{
		if (m_fBlendAlpha + DT * (float)m_iAlphaDiff <= 0.f)
		{
			alpha = 0;
			m_fBlendAlpha = 0.f;
			m_iAlphaDiff = 0;
		}
		else if (m_fBlendAlpha + DT * (float)m_iAlphaDiff >= 255.f)
		{
			alpha = 255;
			m_fBlendAlpha = 255.f;
			m_iAlphaDiff = 0;
		}
		else
		{
			m_fBlendAlpha += float(DT * m_iAlphaDiff);
			alpha = (BYTE)m_fBlendAlpha;
		}
	}
}

void CIcon::render(HDC _dc)
{
	if (nullptr != m_pIcon && m_blendFunc.SourceConstantAlpha != 0)
	{
		Vec2 vImgScale = Vec2((float)m_pIcon->GetWidth(), (float)m_pIcon->GetHeight());
		Vec2 vPos = CObj::GetPos();
		Vec2 vScale = CObj::GetScale();
		AlphaBlend(_dc
			, int(vPos.x - (vScale.x / 2)), int(vPos.y - (vScale.y / 2))
			, int(vScale.x), int(vScale.y)
			, m_pIcon->GetDC()
			, 0, 0
			, int(vImgScale.x), int(vImgScale.y)
			, m_blendFunc);
	}
}

CIcon::CIcon()
	: m_pIcon(nullptr)
	, m_blendFunc{}
	, m_iAlphaDiff(0)
	, m_fBlendAlpha(255.f)
{

	// 백그라운드 이미지 맟추어주기
	m_blendFunc.BlendOp = AC_SRC_OVER;
	m_blendFunc.BlendFlags = 0;

	m_blendFunc.SourceConstantAlpha = 255; // 0 ~ 255
	m_blendFunc.AlphaFormat = AC_SRC_ALPHA; // 0
}
CIcon::~CIcon()
{
}
