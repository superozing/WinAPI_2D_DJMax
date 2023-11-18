#include "pch.h"
#include "CStringTexture.h"
#include "CTexture.h"
#include "CAssetMgr.h"


CStringTexture::CStringTexture()
	: m_blend()
	, m_strTexture(FINDTEX(L"result_black_square"))
{
	m_blend.BlendOp = AC_SRC_OVER;
	m_blend.BlendFlags = 0;
	m_blend.AlphaFormat = AC_SRC_ALPHA; // 0
	m_blend.SourceConstantAlpha = 255;
}

CStringTexture::CStringTexture(const CStringTexture& _Origin)
	: CObj(_Origin)
	, m_blend(_Origin.m_blend)
	, m_strTexture(_Origin.m_strTexture)
{
}

CStringTexture::~CStringTexture()
{
}

void CStringTexture::render(HDC _dc)
{
	if (nullptr != m_strTexture)
	{
		Vec2 vPos = GetPos();
		Vec2 vScale = GetScale();

		AlphaBlend(_dc
			, vPos.x, vPos.y
			, vScale.x, vScale.y
			, m_strTexture->GetDC()
			, 0, 0
			, m_strTexture->GetWidth(), m_strTexture->GetHeight()
			, m_blend);

	}
}

