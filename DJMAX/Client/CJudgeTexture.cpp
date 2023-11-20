#include "pch.h"
#include "CJudgeTexture.h"

#include "CAssetMgr.h"
#include "CAnimator.h"
#include "CGear_PlayLevel.h"


CJudgeTexture::CJudgeTexture()
	:m_arrJudgeTexAnim{}
{
	/* L"judge_txt_max100_1"*/
	//PSJ
	// Load Texture
	m_arrJudgeTexAnim = AddComponent<CAnimator>(L"Judge");
					  
	m_arrJudgeTexAnim->CreateAnimation(L"100",	 FINDTEX(L"judge_txt_max100_atlas")
		,	Vec2(0.f,0.f), Vec2(281.f, 48.f), Vec2(50.f, 20.f), 0.03f, 21);// FINDTEX(L"judge_txt_max100_0");

	m_arrJudgeTexAnim->CreateAnimation(L"90",	 FINDTEX(L"judge_txt_max90_atlas")
		,	Vec2(0.f,0.f), Vec2(210.f, 42.f), Vec2(50.f, 20.f), 0.03f, 21);// FINDTEX(L"judge_txt_max90");

	m_arrJudgeTexAnim->CreateAnimation(L"80",	 FINDTEX(L"judge_txt_max80_atlas")
		,	Vec2(0.f,0.f), Vec2(210.f, 42.f), Vec2(50.f, 20.f), 0.03f, 21);// FINDTEX(L"judge_txt_max80");

	m_arrJudgeTexAnim->CreateAnimation(L"70",	 FINDTEX(L"judge_txt_max70_atlas")
		,	Vec2(0.f,0.f), Vec2(210.f, 42.f), Vec2(50.f, 20.f), 0.03f, 21);// FINDTEX(L"judge_txt_max70");

	m_arrJudgeTexAnim->CreateAnimation(L"60",	 FINDTEX(L"judge_txt_max60_atlas")
		,	Vec2(0.f,0.f), Vec2(210.f, 42.f), Vec2(50.f, 20.f), 0.03f, 21);// FINDTEX(L"judge_txt_max60");

	m_arrJudgeTexAnim->CreateAnimation(L"50",	 FINDTEX(L"judge_txt_max50_atlas")
		,	Vec2(0.f,0.f), Vec2(210.f, 42.f), Vec2(50.f, 20.f), 0.03f, 21);// FINDTEX(L"judge_txt_max50");
	///////////////////////////////////////////////////////////////////////
	m_arrJudgeTexAnim->CreateAnimation(L"40",	 FINDTEX(L"judge_txt_max40_atlas")
		,	Vec2(0.f,0.f), Vec2(188.f, 38.f), Vec2(50.f, 20.f), 0.03f, 21);// FINDTEX(L"judge_txt_max40");

	m_arrJudgeTexAnim->CreateAnimation(L"30",	 FINDTEX(L"judge_txt_max30_atlas")
		,	Vec2(0.f,0.f), Vec2(188.f, 38.f), Vec2(50.f, 20.f), 0.03f, 21);// FINDTEX(L"judge_txt_max30");

	m_arrJudgeTexAnim->CreateAnimation(L"20",	 FINDTEX(L"judge_txt_max20_atlas")
		,	Vec2(0.f,0.f), Vec2(188.f, 38.f), Vec2(50.f, 20.f), 0.03f, 21);// FINDTEX(L"judge_txt_max20");

	m_arrJudgeTexAnim->CreateAnimation(L"10",	 FINDTEX(L"judge_txt_max10_atlas")
		,	Vec2(0.f,0.f), Vec2(188.f, 38.f), Vec2(50.f, 20.f), 0.03f, 21);// FINDTEX(L"judge_txt_max10");

	m_arrJudgeTexAnim->CreateAnimation(L"1",	 FINDTEX(L"judge_txt_max1_atlas")
		,	Vec2(0.f,0.f), Vec2(159.f, 36.f), Vec2(50.f, 20.f), 0.03f, 21);// FINDTEX(L"judge_txt_max1");

	m_arrJudgeTexAnim->CreateAnimation(L"BREAK", FINDTEX(L"judge_txt_break_atlas")
		,	Vec2(0.f,0.f), Vec2(121.f, 30.f), Vec2(50.f, 20.f), 0.03f, 21);// FINDTEX(L"judge_txt_break");
}

CJudgeTexture::~CJudgeTexture()
{
}

void CJudgeTexture::tick(float _DT)
{
	CObj::tick(_DT);
}

void CJudgeTexture::render(HDC _dc)
{
	CObj::render(_dc);
	if (m_pOwnerGear != nullptr)
		m_pOwnerGear->EndRender(_dc);
}

void CJudgeTexture::SetJudgeAnimation(JUDGE_VECTOR_IDX _JudgeIndex)
{
	switch (_JudgeIndex)
	{
	case JUDGE_VECTOR_IDX::_100:
		m_arrJudgeTexAnim->Play(L"100", false);
		break;
	case JUDGE_VECTOR_IDX::_90:
		m_arrJudgeTexAnim->Play(L"90", false);
		break;
	case JUDGE_VECTOR_IDX::_80:
		m_arrJudgeTexAnim->Play(L"80", false);		
		break;
	case JUDGE_VECTOR_IDX::_70:
		m_arrJudgeTexAnim->Play(L"70", false);		
		break;
	case JUDGE_VECTOR_IDX::_60:
		m_arrJudgeTexAnim->Play(L"60", false);		
		break;
	case JUDGE_VECTOR_IDX::_50:
		m_arrJudgeTexAnim->Play(L"50", false);		
		break;
	case JUDGE_VECTOR_IDX::_40:
		m_arrJudgeTexAnim->Play(L"40", false);		
		break;
	case JUDGE_VECTOR_IDX::_30:
		m_arrJudgeTexAnim->Play(L"30", false);		
		break;
	case JUDGE_VECTOR_IDX::_20:
		m_arrJudgeTexAnim->Play(L"20", false);		
		break;
	case JUDGE_VECTOR_IDX::_10:
		m_arrJudgeTexAnim->Play(L"10", false);		
		break;
	case JUDGE_VECTOR_IDX::_1:
		m_arrJudgeTexAnim->Play(L"1", false);		
		break;
	case JUDGE_VECTOR_IDX::BREAK:
		m_arrJudgeTexAnim->Play(L"BREAK", false);		
		break;
	default:
		break;
	}
}
