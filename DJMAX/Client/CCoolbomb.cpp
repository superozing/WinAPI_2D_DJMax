#include "pch.h"
#include "CCoolbomb.h"
#include "CAnimator.h"

#include "CAssetMgr.h"

CCoolbomb::CCoolbomb()
	:m_CoolbombAnimArr{}
{
	CObj::SetPos(Vec2(158, 630));

	for (int i = 0; i < 4; ++i)
	{
		m_CoolbombAnimArr[i] = AddComponent<CAnimator>(L"CoolBomb");

		m_CoolbombAnimArr[i]->CreateAnimation(L"Coolbomb"
											, FINDTEX(L"coolbomb_atlas_size_50")
											, Vec2(0.f, 0.f), Vec2(213, 213)
											, Vec2(100.f * i, 0.f)
											, 0.01f, 16);
		m_CoolbombAnimArr[i]->CreateAnimation(L"CoolbombMax"
											, FINDTEX(L"coolbomb_max_atlas_size_50")
											, Vec2(0.f, 0.f), Vec2(213, 213)
											, Vec2(100.f * i, 0.f)
											, 0.01f, 16);
	}
}

CCoolbomb::~CCoolbomb()
{
}


void CCoolbomb::tick(float _DT)
{
	CObj::tick(_DT);
}

void CCoolbomb::render(HDC _dc)
{
	CObj::render(_dc);
}

void CCoolbomb::PlayCoolbombAnimation(GEARLINE_TYPE _line, JUDGE_VECTOR_IDX _Judge)
{
	if (_Judge == JUDGE_VECTOR_IDX::BREAK) return;

	static wstring coolbomb_str;

	if (_Judge <= JUDGE_VECTOR_IDX::_90)	coolbomb_str = L"CoolbombMax";
	else									coolbomb_str = L"Coolbomb";

	switch (_line)
	{
	case GEARLINE_TYPE::_1:
			m_CoolbombAnimArr[0]->Play(coolbomb_str, false);
		break;
	case GEARLINE_TYPE::_2:
			m_CoolbombAnimArr[1]->Play(coolbomb_str, false);
		break;
	case GEARLINE_TYPE::_3:
			m_CoolbombAnimArr[2]->Play(coolbomb_str, false);
		break;
	case GEARLINE_TYPE::_4:
			m_CoolbombAnimArr[3]->Play(coolbomb_str, false);
		break;
	}

}
