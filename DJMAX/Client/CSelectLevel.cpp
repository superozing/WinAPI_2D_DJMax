#include "pch.h"

#include "CAssetMgr.h"
#include "CKeyMgr.h"
#include "CLevelMgr.h"

#include "CBackground.h"
#include "CBackground_alpha.h"
#include "CFocusUI.h"
#include "CMusicAlbumTex.h"
#include "CMusicInfo.h"
#include "CMusicSelectBar.h"
#include "CNumTexture.h"
#include "CSelectLevel.h"
#include "CStringTexture.h"

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

	m_MusicInfo = new CMusicInfo(this);

	m_MusicInfo->AddMusicInfo(FINDSND(L"Grievous Lady"), L"GrievousLady"
		, FINDTEX(L"GrievousLady_MusicNameTex")
		, FINDTEX(L"GrievousLady_MainTex")
		, FINDTEX(L"GrievousLady_AlbumTex")
		, 105
		, 0
		, 0
		, 13);

	m_MusicInfo->AddMusicInfo(FINDSND(L"Altale"), L"Altale"
		, FINDTEX(L"Altale_MusicNameTex")
		, FINDTEX(L"Altale_MainTex")
		, FINDTEX(L"Altale_AlbumTex")
		, 90
		, 295213
		, 501
		, -14);

	m_MusicInfo->GetSelectBar().operator[](0)->GetFocusUI()->SetPressedImg(FINDTEX(L"GrievousLady_Select"));
	m_MusicInfo->GetSelectBar().operator[](0)->GetFocusUI()->SetNormalImg(FINDTEX(L"GrievousLady_UnSelect"));

	m_MusicInfo->GetSelectBar().operator[](1)->GetFocusUI()->SetPressedImg(FINDTEX(L"Altale_Select"));
	m_MusicInfo->GetSelectBar().operator[](1)->GetFocusUI()->SetNormalImg(FINDTEX(L"Altale_UnSelect"));

	AddObject(LAYER::UI, m_MusicInfo);

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

	if (KEY_TAP(KEY::ENTER))
	{
		CLevelMgr::GetInst()->SetCurMusicInfo(m_MusicInfo->GetMusicInfo());
		CLevelMgr::GetInst()->GetCurMusicInfo();
		ChangeLevel(LEVEL_TYPE::PLAY_LEVEL);
	}
}
