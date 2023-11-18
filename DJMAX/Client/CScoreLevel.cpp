#include "pch.h"
#include "CScoreLevel.h"
#include "CCamera.h"
#include "CBackground.h"
#include "CBackground_alpha.h"
#include "CAssetMgr.h"

#include "CSound.h"
#include "CCircle.h"
#include "CPlayRank.h"

void CScoreLevel::init()
{
#pragma region Background
	CBackground* pBackground = new CBackground;
	pBackground->SetTexture(FINDTEX(L"background_default"));
	AddObject(LAYER::BACK_GROUND, pBackground);

	CBackground_alpha* pBgAlpha = new CBackground_alpha;
	pBgAlpha->SetTexture(FINDTEX(L"background_shine"));
	pBgAlpha->SetAlpha(255);
	AddObject(LAYER::BACK_GROUND, pBgAlpha);

	pBackground = new CBackground;
	pBackground->SetTexture(FINDTEX(L"background_strip_square"));
	pBackground->SetAlpha(65);
	pBackground->SetMaxAlpha(150);
	AddObject(LAYER::BACK_GROUND, pBackground);
#pragma endregion
	CCircle* pCircle = new CCircle();
	AddObject(LAYER::GEAR, pCircle);

	pPlayRank = new CPlayRank();
	AddObject(LAYER::GEAR, pPlayRank);

#pragma region _	MUSIC

	m_ClearMusic = FINDSND(L"music_clear");
	m_ClearMusic->SetVolume(80);


#pragma endregion

#pragma region _	

}

void CScoreLevel::enter()
{
	CCamera::GetInst()->FadeIn(1.f);
	m_ClearMusic->Play();
	int AccJudge = 0;
	int size = 0;

	for (int i = 0; i < m_vecJudge->size(); ++i)
	{
		AccJudge += 10 * ((10 - i) * m_vecJudge->operator[](i));
		size += m_vecJudge->operator[](i);
	}

	float JudgePercent = (float)AccJudge / size;

	if (AccJudge != 0 && AccJudge == 100.f * m_vecJudge->operator[](0))
		pPlayRank->SetRank(PLAY_RANK_IDX::PERFECT_PLAY);
	else if (!m_vecJudge->operator[](11))
		pPlayRank->SetRank(PLAY_RANK_IDX::MAX_COMBO);
	else if (JudgePercent >= 97.f)
		pPlayRank->SetRank(PLAY_RANK_IDX::S);
	else if (JudgePercent >= 90.f)
		pPlayRank->SetRank(PLAY_RANK_IDX::A);
	else if (JudgePercent >= 80.f)
		pPlayRank->SetRank(PLAY_RANK_IDX::B);
	else
		pPlayRank->SetRank(PLAY_RANK_IDX::C);
}

void CScoreLevel::exit()
{
	m_ClearMusic->Stop();

}

void CScoreLevel::tick()
{
	CLevel::tick();
}
