#include "pch.h"
#include "CSelectLevel.h"
#include "CBackground.h"
#include "CBackground_alpha.h"

#include "CAssetMgr.h"
#include "CStringTexture.h"
#include "CNumTexture.h"
#include "CMusicInfo.h"

void CSelectLevel::init()
{
	

#pragma region Background

	CBackground_alpha* pBgAlpha = new CBackground_alpha;
	pBgAlpha->SetTexture(FINDTEX(L"background_shine"));
	pBgAlpha->SetAlpha(150);
	pBgAlpha->SmoothChangeAlpha(255);
	AddObject((LAYER)0, pBgAlpha);

	CBackground* pBackground = new CBackground;
	pBackground->SetTexture(FINDTEX(L"background_selectLevelMain"));
	AddObject((LAYER)2, pBackground);

#pragma endregion


#pragma region _	MUSICINFO INIT

	m_MusicInfo = new CMusicInfo;

	m_MusicInfo->AddMusicInfo(FINDSND(L"Grievous Lady"), L"Grievous Lady"
		, FINDTEX(L"Grievous Lady_MusicNameTex")
		, FINDTEX(L"Grievous Lady_MainTex")
		, FINDTEX(L"Grievous Lady_AlbumTex")
		, 105
		, 0
		, 0);

	m_MusicInfo->AddMusicInfo(FINDSND(L"Altale"), L"Altale"
		, FINDTEX(L"Altale_MusicNameTex")
		, FINDTEX(L"Altale_MainTex")
		, FINDTEX(L"Altale_MainTex")
		, 90
		, 0
		, 0);

#pragma endregion
}

void CSelectLevel::enter()
{
	CCamera::GetInst()->FadeIn(1.f);
}

void CSelectLevel::exit()
{


	DeleteAllObjects();
}

void CSelectLevel::tick()
{
	CLevel::tick();


}
