#include "pch.h"
#include "CCircle.h"
#include "CAssetMgr.h"
#include "CTimeMgr.h"
#include "CTexture.h"

CCircle::CCircle()
	:m_CircleTex(FINDTEX(L"blackCircle"))
{
	SetPos(Vec2(400, 450));
	SetScale(Vec2(512, 512));

}

CCircle::~CCircle()
{
}



void CCircle::tick(float _DT)
{
}

void CCircle::render(HDC _dc)
{
	static BLENDFUNCTION m_blend;
	m_blend.BlendOp = AC_SRC_OVER;
	m_blend.BlendFlags = 0;
	m_blend.AlphaFormat = AC_SRC_ALPHA; // 0
	m_blend.SourceConstantAlpha = 160;
	static float diameterRatio = .0f;
	Vec2 Pos = GetPos();
	Vec2 Scale = GetScale();
	AlphaBlend(_dc
		, Pos.x - ((Scale.x / 2) * (diameterRatio / 100)), Pos.y - ((Scale.y / 2) * (diameterRatio / 100))
		, Scale.x * (diameterRatio / 100), Scale.y * (diameterRatio / 100)
		, m_CircleTex->GetDC()
		, 0, 0
		, 512, 512
		, m_blend);
	if (diameterRatio < 100.f)
	{
		diameterRatio += 125.f * DT;
		if (diameterRatio > 100.f)
		{
			diameterRatio = 100.f;
		}
	}

}

