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

#pragma region _	NUMBER
	m_numTexArr		= new CNumTexture[3];
	m_JudgePercent	= new CNumTexture(1.2f);

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
		JudgeArr[1] += 100 * m_vecJudge->operator[](i);
	}

	// 1% 판정
	AllJudgeBuf += m_vecJudge->operator[](JIDX::_1);
	JudgeArr[1] += m_vecJudge->operator[](JIDX::_1);

	// break 판정
	JudgeArr[2]	= m_vecJudge->operator[](JIDX::BREAK);

	// 이 시점에서, AllJudgeBuf에는 모든 판정 점수가 들어 있으니 이 것을 벡터 전체 개수로 나누면 판정이 나오겠죠? 물론 실수 값으로.
	float PlayPercent = (float)AllJudgeBuf / m_vecJudge->size();

	// 텍스트도 설정해주기.
	m_JudgePercent->SetRealNum(PlayPercent);
	m_TotalScore->SetRealNum(350000 * (PlayPercent / 100));
	for (int i = 0; i < 3; ++i) m_numTexArr[i].SetIntNum(JudgeArr[i]);

	// 이제 이 플레이 퍼센트에 따라서 플레이 랭크를 정해주면 되겠네요.
	if (PlayPercent == 100.f)						pPlayRank->SetRank(PLAY_RANK_IDX::PERFECT_PLAY);
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
