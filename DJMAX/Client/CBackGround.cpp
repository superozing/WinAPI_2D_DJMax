#include "pch.h"
#include "CBackGround.h"

#include "CEngine.h"

#include "CAssetMgr.h"
#include "CTexture.h"
#include "CTimeMgr.h"

CBackground::CBackground()
	: m_bg(nullptr)
	, m_blendFunc{}
	, m_iAlphaDiff(0)
	, m_fBlendAlpha(.0f)
{
	// 화면의 크기로 Pos와 Scale을 "무조건 동일하게" 맟춤.
	POINT pPtResolution = CEngine::GetInst()->GetResolution();
	Super::SetPos(Vec2(0.f,0.f));
	Super::SetScale(Vec2((float)pPtResolution.x, (float)pPtResolution.y));

	// 백그라운드 이미지 맟추어주기
	m_blendFunc.BlendOp = AC_SRC_OVER;
	m_blendFunc.BlendFlags = 0;

	m_blendFunc.SourceConstantAlpha = 255; // 0 ~ 255
	m_blendFunc.AlphaFormat = AC_SRC_ALPHA; // 0
}

CBackground::CBackground(const CBackground& _Origin)
	: m_bg(nullptr)
	, m_blendFunc{}
	, m_iAlphaDiff(0)
	, m_fBlendAlpha(.0f)
{
}

CBackground::~CBackground()
{
}

void CBackground::tick(float _DT)
{
	if (m_iAlphaDiff != 0)
	{
		if (m_blendFunc.SourceConstantAlpha + m_iAlphaDiff <= 0)
		{
			m_blendFunc.SourceConstantAlpha = 0;
			m_fBlendAlpha = 0.f;
			m_iAlphaDiff = 0;
		}
		else if (m_blendFunc.SourceConstantAlpha + m_iAlphaDiff >= 255)
		{
			m_blendFunc.SourceConstantAlpha = 255;
			m_fBlendAlpha = 255.f;
			m_iAlphaDiff = 0;
		}
		else
		{
			m_fBlendAlpha += float(DT * m_iAlphaDiff);
			m_blendFunc.SourceConstantAlpha = m_fBlendAlpha;
		}
	}
}

void CBackground::render(HDC _dc)
{
	Super::render(_dc);

	if (nullptr != m_bg && m_blendFunc.SourceConstantAlpha != 0)
	{
		static Vec2 vImgScale	= Vec2((float)m_bg->GetWidth(), (float)m_bg->GetHeight());
		static Vec2 vPos		= Super::GetPos();
		static Vec2 vScale		= Super::GetScale();
		AlphaBlend(_dc
			, int(vPos.x), int(vPos.y)
			, int(vScale.x), int(vScale.y)
			, m_bg->GetDC()
			, 0, 0
			, int(vImgScale.x), int(vImgScale.y)
			, m_blendFunc);
	}
}

