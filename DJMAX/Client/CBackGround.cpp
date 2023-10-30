#include "pch.h"
#include "CBackGround.h"

#include "CEngine.h"

#include "CAssetMgr.h"
#include "CTexture.h"


CBackGround::CBackGround()
	:m_bg(nullptr)
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

CBackGround::CBackGround(const CBackGround& _Origin)
{
}

CBackGround::~CBackGround()
{
}

void CBackGround::render(HDC _dc)
{
	Super::render(_dc);

	if (nullptr != m_bg)
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

