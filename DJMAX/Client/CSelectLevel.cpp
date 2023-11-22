#include "pch.h"
#include "CSelectLevel.h"
#include "CBackground.h"
#include "CBackground_alpha.h"

#include "CAssetMgr.h"
#include "CStringTexture.h"
#include "CNumTexture.h"
#include "CMusicInfo.h"
#include "CMusicAlbumTex.h"

void CSelectLevel::init()
{
	

#pragma region Background

	CBackground* pBgAlpha = new CBackground;
	pBgAlpha->SetTexture(FINDTEX(L"background_shine"));
	pBgAlpha->SetAlpha(150);
	AddObject((LAYER)0, pBgAlpha);

	CBackground* pBackground = new CBackground;
	pBackground->SetTexture(FINDTEX(L"background_selectLevelMain"));
	AddObject((LAYER)2, pBackground);

#pragma endregion


#pragma region _	MUSICINFO INIT

	m_MusicInfo = new CMusicInfo;

	m_MusicInfo->AddMusicInfo(FINDSND(L"Grievous Lady"), L"GrievousLady"
		, FINDTEX(L"GrievousLady_MusicNameTex")
		, FINDTEX(L"GrievousLady_MainTex")
		, FINDTEX(L"GrievousLady_AlbumTex")
		, 105
		, 0
		, 0);

	m_MusicInfo->AddMusicInfo(FINDSND(L"Altale"), L"Altale"
		, FINDTEX(L"Altale_MusicNameTex")
		, FINDTEX(L"Altale_MainTex")
		, FINDTEX(L"Altale_AlbumTex")
		, 90
		, 0
		, 0);

	AddObject((LAYER)3, m_MusicInfo);

	CMusicAlbumTex* pMusicAlbumTex = new CMusicAlbumTex(m_MusicInfo);
	AddObject((LAYER)1, pMusicAlbumTex);
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
	CLevel::tick();


}
