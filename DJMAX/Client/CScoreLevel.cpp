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
	// ���� ��� �� �ؾ� �ϴ� ���� �����.
	// 1. ��Ȯ���� ����ϰ� �ѹ� �ؽ��Ŀ� �ֱ�
	// 3. �÷��� �����κ��� �޾ƿ� ������ �ѹ��ؽ��Ŀ� �ֱ�
	// 4. ���� �ۼ�Ʈ ���� �Էµ� ������ �����ֱ�


	// ��Ȯ���� ����ϱ� ���� �迭. ������� 100, 90~1, break�� ������.
	int JudgeArr[3] = { 0,0,0 };

	int AllJudgeBuf = 0;

	// 100% ����
	AllJudgeBuf += 100 * m_vecJudge->operator[](JIDX::_100);
	JudgeArr[JIDX::_100] += m_vecJudge->operator[](JIDX::_100);

	// 90 ~ 10% ����
	for (int i = 1; i < 10; ++i)
	{
		AllJudgeBuf += (100 - i*10) * m_vecJudge->operator[](i);
		JudgeArr[1] += 100 * m_vecJudge->operator[](i);
	}

	// 1% ����
	AllJudgeBuf += m_vecJudge->operator[](JIDX::_1);
	JudgeArr[1] += m_vecJudge->operator[](JIDX::_1);

	// break ����
	JudgeArr[2]	= m_vecJudge->operator[](JIDX::BREAK);

	// �� ��������, AllJudgeBuf���� ��� ���� ������ ��� ������ �� ���� ���� ��ü ������ ������ ������ ��������? ���� �Ǽ� ������.
	float PlayPercent = (float)AllJudgeBuf / m_vecJudge->size();

	// �ؽ�Ʈ�� �������ֱ�.
	m_JudgePercent->SetRealNum(PlayPercent);
	m_TotalScore->SetRealNum(350000 * (PlayPercent / 100));
	for (int i = 0; i < 3; ++i) m_numTexArr[i].SetIntNum(JudgeArr[i]);

	// ���� �� �÷��� �ۼ�Ʈ�� ���� �÷��� ��ũ�� �����ָ� �ǰڳ׿�.
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


	// �ڵ尡 ������� ���� �Ⱦ �Լ�ȭ �߽��ϴ�.
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
