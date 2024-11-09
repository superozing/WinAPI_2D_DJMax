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
#include "CSpeedTexture.h"
#include "CMusicDifficult.h"
#include "struct.h"

void CSelectLevel::init()
{
#pragma region _	Background

	CBackground* pBgAlpha = new CBackground;
	pBgAlpha->SetTexture(FINDTEX(L"background_shine"));
	pBgAlpha->SetAlpha(150);
	AddObject((LAYER)0, pBgAlpha);

	CBackground* pBackground = new CBackground;
	pBackground->SetTexture(FINDTEX(L"background_selectLevelMain"));
	AddObject((LAYER)2, pBackground);

#pragma endregion

#pragma region _	SpeedIcon

	m_Speed = new CSpeedTexture();
	m_Speed->SetPos(Vec2(120, 690));
	AddObject(LAYER::ONTHEUI, m_Speed);

#pragma endregion

#pragma region _	MUSICINFO INIT

	m_MusicInfo = new CMusicInfo(this);

#pragma region _		 SetMusicInfo

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
		, 0
		, 0
		, -14);

	m_MusicInfo->AddMusicInfo(FINDSND(L"Grievous Lady"), L"defaultNote");
	m_MusicInfo->AddMusicInfo(FINDSND(L"Grievous Lady"), L"longNote");
	m_MusicInfo->AddMusicInfo(FINDSND(L"Grievous Lady"), L"sideNote");
	m_MusicInfo->AddMusicInfo(FINDSND(L"Grievous Lady"), L"combo");
	m_MusicInfo->AddMusicInfo(FINDSND(L"Grievous Lady"), L"Test");
#pragma endregion

#pragma region _		 SetImg
	m_MusicInfo->GetSelectBar()[0]->GetFocusUI()->SetPressedImg(FINDTEX(L"GrievousLady_Select"));
	m_MusicInfo->GetSelectBar()[0]->GetFocusUI()->SetNormalImg(FINDTEX(L"GrievousLady_UnSelect"));

	m_MusicInfo->GetSelectBar()[1]->GetFocusUI()->SetPressedImg(FINDTEX(L"Altale_Select")); 
	m_MusicInfo->GetSelectBar()[1]->GetFocusUI()->SetNormalImg(FINDTEX(L"Altale_UnSelect"));

	for (int i = 0; i < 5; ++i)
	{
		m_MusicInfo->GetSelectBar()[i + 2]->GetFocusUI()->SetPressedImg(FINDTEX(L"default_Select"));
		m_MusicInfo->GetSelectBar()[i + 2]->GetFocusUI()->SetNormalImg(FINDTEX(L"default_UnSelect"));
	}
#pragma endregion

	AddObject(LAYER::UI, m_MusicInfo);

	CMusicAlbumTex* pMusicAlbumTex = new CMusicAlbumTex(m_MusicInfo);
	AddObject((LAYER)1, pMusicAlbumTex);

	m_musicDifficult = new CMusicDifficult;
	m_musicDifficult->SetPos(Vec2(80, 400));
	AddObject(LAYER::ONTHEUI, m_musicDifficult);


	m_pNumTex1 = new CNumTexture;
	m_pNumTex1->SetFontSize(40);
	m_pNumTex1->SetPos(Vec2(140, 595));
	AddObject(LAYER::ONTHEUI, m_pNumTex1);
	
	m_pNumTex2 = new CNumTexture;
	m_pNumTex2->SetFontSize(40);
	m_pNumTex2->SetPos(Vec2(375, 595));
	AddObject(LAYER::ONTHEUI, m_pNumTex2);

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
	
	m_pNumTex1->SetIntNum(CLevelMgr::GetInst()->GetBestCombo());
	m_pNumTex2->SetIntNum(CLevelMgr::GetInst()->GetComboBuf());

	if (KEY_TAP(KEY::ENTER))
	{
		CLevelMgr::GetInst()->SetCurMusicInfo(m_MusicInfo->GetMusicInfo());
		CLevelMgr::GetInst()->GetCurMusicInfo();
		CLevelMgr::GetInst()->SetSpeed(m_Speed->GetSpeed());
		CLevelMgr::GetInst()->SetMusicDifficult(m_musicDifficult->GetDifficult());
		
		ChangeLevel(LEVEL_TYPE::PLAY_LEVEL);
	}


}
