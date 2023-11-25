#include "pch.h"
#include "CScoreLevel.h"
#include "CCamera.h"
#include "CBackground.h"
#include "CBackground_alpha.h"
#include "CAssetMgr.h"

#include "CSound.h"
#include "CCircle.h"
#include "CPlayRank.h"
#include "CNumTexture.h"
#include "CStringTexture.h"
#include "CMusicDifficult.h"
#include "CLevelMgr.h"

void CScoreLevel::init()
{
#pragma region Background
	CBackground* pBackground = new CBackground;
	pBackground->SetTexture(FINDTEX(L"background_default"));
	AddObject((LAYER)SCORE_LAYER::S_BACK_GROUND, pBackground);

	CBackground_alpha* pBgAlpha = new CBackground_alpha;
	pBgAlpha->SetTexture(FINDTEX(L"background_shine"));
	pBgAlpha->SetAlpha(255);
	AddObject((LAYER)SCORE_LAYER::S_BACK_GROUND, pBgAlpha);


#pragma endregion
	CCircle* pCircle = new CCircle();
	AddObject((LAYER)SCORE_LAYER::S_OBJECT, pCircle);

	pPlayRank = new CPlayRank();
	AddObject((LAYER)SCORE_LAYER::S_OBJECT, pPlayRank);

	CStringTexture* pStrTex = new CStringTexture;
	pStrTex->SetTexture(FINDTEX(L"result_black_square"));
	pStrTex->SetPos(Vec2(1600, 450));
	pStrTex->SetScale(Vec2(1000, 1000));
	pStrTex->SetAlpha(150);
	AddObject((LAYER)SCORE_LAYER::S_OBJECT, pStrTex);
	
#pragma region _	MUSIC

	m_ClearMusic = FINDSND(L"music_clear");
	m_ClearMusic->SetVolume(80);

	m_MusicDifficult = new CMusicDifficult;
	m_MusicDifficult->SetDifficult(CLevelMgr::GetInst()->GetMusicDifficult());
	m_MusicDifficult->SetPos(Vec2(195,730));
	AddObject(LAYER::ONTHEUI, m_MusicDifficult);
#pragma endregion

#pragma region _	NUMBER
	m_numTexArr[0] = new CNumTexture;
	m_numTexArr[1] = new CNumTexture;
	m_numTexArr[2] = new CNumTexture;


	/////result_icon_max100
	pStrTex = new CStringTexture;
	m_numTexArr[0]->SetPos(Vec2(850, 300));
	m_numTexArr[0]->SetFontSize(50);
	pStrTex->SetTexture(FINDTEX(L"result_icon_max100"));
	pStrTex->SetPos(Vec2(830, 260));
	pStrTex->SetScale(Vec2(189, 35));
	pStrTex->SetAlpha(150);
	AddObject((LAYER)SCORE_LAYER::S_ICON, pStrTex);




	/////result_icon_max190
	m_numTexArr[1]->SetPos(Vec2(1250, 300));
	m_numTexArr[1]->SetFontSize(50); 
	m_numTexArr[0]->SetTexture(FINDTEX(L"num_atlas_lineless"));
	m_numTexArr[1]->SetTexture(FINDTEX(L"num_atlas_lineless"));
	m_numTexArr[2]->SetTexture(FINDTEX(L"num_atlas_lineless"));
	pStrTex = new CStringTexture;
	pStrTex->SetTexture(FINDTEX(L"result_icon_max190"));
	pStrTex->SetPos(Vec2(1230, 260));
	pStrTex->SetScale(Vec2(188, 35));
	pStrTex->SetAlpha(150);
	AddObject((LAYER)SCORE_LAYER::S_ICON, pStrTex);



	/////result_icon_break
	m_numTexArr[2]->SetPos(Vec2(850, 500));
	m_numTexArr[2]->SetFontSize(50);
	pStrTex = new CStringTexture;
	pStrTex->SetPos(Vec2(830, 460));
	pStrTex->SetScale(Vec2(131, 34));
	pStrTex->SetAlpha(150);
	pStrTex->SetTexture(FINDTEX(L"result_icon_break"));
	AddObject((LAYER)SCORE_LAYER::S_ICON, pStrTex);




	/////result_icon_maxcombo
	pStrTex = new CStringTexture;
	pStrTex->SetTexture(FINDTEX(L"result_icon_maxcombo"));
	pStrTex->SetPos(Vec2(1230, 460));
	pStrTex->SetScale(Vec2(213, 35));
	pStrTex->SetAlpha(150);
	AddObject((LAYER)SCORE_LAYER::S_ICON, pStrTex);

	

	AddObject((LAYER)SCORE_LAYER::S_SCORE, m_numTexArr[0]);
	AddObject((LAYER)SCORE_LAYER::S_SCORE, m_numTexArr[1]);
	AddObject((LAYER)SCORE_LAYER::S_SCORE, m_numTexArr[2]);

	///// m_JudgePercent
	m_JudgePercent	= new CNumTexture;
	m_JudgePercent->SetTexture(FINDTEX(L"num_atlas_lineless"));
	m_JudgePercent->SetPos(Vec2(310, 780));
	m_JudgePercent->SetFontSize(50);
	AddObject((LAYER)SCORE_LAYER::S_SCORE, m_JudgePercent);



	///// result_icon_score
	m_TotalScore	= new CNumTexture;
	m_TotalScore->SetTexture(FINDTEX(L"num_atlas_lineless"));
	m_TotalScore->SetPos(Vec2(800, 700));
	m_TotalScore->SetFontSize(200);
	pStrTex = new CStringTexture;
	pStrTex->SetTexture(FINDTEX(L"result_icon_score"));
	pStrTex->SetPos(Vec2(810, 650));
	pStrTex->SetScale(Vec2(132, 35));
	pStrTex->SetAlpha(150);
	AddObject((LAYER)SCORE_LAYER::S_ICON, pStrTex);
	AddObject((LAYER)SCORE_LAYER::S_SCORE, m_TotalScore);

#pragma endregion




	

	
}

#define JIDX (ULONGLONG)JUDGE_VECTOR_IDX

void CScoreLevel::JudgeScoreEnter()
{
	// 판정 계산 시 해야 하는 일을 적어보자.
	// 1. 정확도를 계산하고 넘버 텍스쳐에 넣기
	// 3. 플레이 레벨로부터 받아온 점수를 넘버텍스쳐에 넣기
	// 4. 판정 퍼센트 별로 입력된 개수를 보여주기


	// 정확도를 계산하기 위한 배열. 순서대로 100, 90~1, break로 보여줌.
	int JudgeArr[3] = { 0,0,0 };

	int AllJudgeBuf = 0;

	// 100% 판정
	AllJudgeBuf += 100 * m_vecJudge->operator[](JIDX::_100);
	JudgeArr[JIDX::_100] += m_vecJudge->operator[](JIDX::_100);

	// 90 ~ 10% 판정
	for (int i = 1; i < 10; ++i)
	{
		AllJudgeBuf += (100 - i*10) * m_vecJudge->operator[](i);
		JudgeArr[1] += m_vecJudge->operator[](i);
	}

	// 1% 판정
	AllJudgeBuf += m_vecJudge->operator[](JIDX::_1);
	JudgeArr[1] += m_vecJudge->operator[](JIDX::_1);

	// break 판정
	JudgeArr[2]	= m_vecJudge->operator[](JIDX::BREAK);

	// 이 시점에서, AllJudgeBuf에는 모든 판정 점수가 들어 있으니 이 것을 벡터 전체 개수로 나누면 판정이 나오겠죠? 물론 실수 값으로.
	float PlayPercent = (float)AllJudgeBuf / (JudgeArr[0] + JudgeArr[1] + JudgeArr[2]);

	// 텍스트도 설정해주기.
	m_JudgePercent->SetRealNum(PlayPercent);
	m_TotalScore->SetIntNum(350000 * (PlayPercent / 100));
	for (int i = 0; i < 3; ++i) m_numTexArr[i]->SetIntNum(JudgeArr[i]);

	// 이제 이 플레이 퍼센트에 따라서 플레이 랭크를 정해주면 되겠네요.
	if		(PlayPercent == 100.f)					pPlayRank->SetRank(PLAY_RANK_IDX::PERFECT_PLAY);
	else if (!m_vecJudge->operator[](JIDX::BREAK))	pPlayRank->SetRank(PLAY_RANK_IDX::MAX_COMBO);
	else if (PlayPercent >= 97.f)					pPlayRank->SetRank(PLAY_RANK_IDX::S);
	else if (PlayPercent >= 90.f)					pPlayRank->SetRank(PLAY_RANK_IDX::A);
	else if (PlayPercent >= 80.f)					pPlayRank->SetRank(PLAY_RANK_IDX::B);
	else											pPlayRank->SetRank(PLAY_RANK_IDX::C);



}

#undef JIDX

void CScoreLevel::enter()
{
	CCamera::GetInst()->FadeIn(1.f);
	m_ClearMusic->Play();


	// 코드가 길어지는 것이 싫어서 함수화 했습니당.
	JudgeScoreEnter();
}

void CScoreLevel::exit()
{
	m_ClearMusic->Stop();

}

void CScoreLevel::tick()
{
	CLevel::tick();
}
