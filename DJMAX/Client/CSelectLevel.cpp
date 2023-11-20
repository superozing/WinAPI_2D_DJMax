#include "pch.h"
#include "CSelectLevel.h"
#include "CBackground.h"
#include "CBackground_alpha.h"

#include "CAssetMgr.h"

void CSelectLevel::init()
{
	

#pragma region Background
	// pBackground = new CBackground;
	//pBackground->SetTexture(FINDTEX(L"background_default"));
	//AddObject((LAYER)SCORE_LAYER::S_BACK_GROUND, pBackground);

	CBackground_alpha* pBgAlpha = new CBackground_alpha;
	pBgAlpha->SetTexture(FINDTEX(L"background_shine"));
	pBgAlpha->SetAlpha(150);
	pBgAlpha->SmoothChangeAlpha(255);
	AddObject((LAYER)SCORE_LAYER::S_BACK_GROUND, pBgAlpha);

	CBackground* pBackground = new CBackground;
	pBackground->SetTexture(FINDTEX(L"background_selectLevelMain"));
	AddObject((LAYER)SCORE_LAYER::S_BACK_GROUND, pBackground);
	

#pragma endregion
}

void CSelectLevel::enter()
{
	CCamera::GetInst()->FadeIn(1.f);
}

void CSelectLevel::exit()
{
}

void CSelectLevel::tick()
{
}
