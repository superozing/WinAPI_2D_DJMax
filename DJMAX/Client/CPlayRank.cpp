#include "pch.h"
#include "CPlayRank.h"
#include "CAssetMgr.h"
#include "CTexture.h"
#include "CTimeMgr.h"

CPlayRank::CPlayRank()
	:m_RankAtlas(FINDTEX(L"rank_atlas"))
	,m_PlayRankIdx(0)
	,diameterRatio(-300.f)
{
}

CPlayRank::~CPlayRank()
{
}

void CPlayRank::render(HDC _dc)
{
	CObj::render(_dc);

	BLENDFUNCTION m_blend;
	m_blend.BlendOp = AC_SRC_OVER;
	m_blend.BlendFlags = 0;
	m_blend.AlphaFormat = AC_SRC_ALPHA; // 0
	m_blend.SourceConstantAlpha = 255;

	AlphaBlend(_dc
		, 400 - (275.f * diameterRatio / 100.f), 430 - (275.f * diameterRatio / 100)
		, 550 * (diameterRatio / 100), 550 * (diameterRatio / 100)
		, m_RankAtlas->GetDC()
		, 550 * m_PlayRankIdx, 0
		, 550, 550
		, m_blend);

	if (diameterRatio < 100.f)
	{
		diameterRatio += 400.f * DT;
		if (diameterRatio > 100.f)
		{
			diameterRatio = 100.f;
		}
	}
}

