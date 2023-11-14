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

void CCoolbomb::PlayCoolbombAnimation(GEARLINE_TYPE _line, bool _isMaxJudge)
{
	switch (_line)
	{
	case GEARLINE_TYPE::_1:
	{
		if (_isMaxJudge)
			m_CoolbombAnimArr[0]->Play(L"CoolbombMax", false);
		else
			m_CoolbombAnimArr[0]->Play(L"Coolbomb", false);
	}
		break;

	case GEARLINE_TYPE::_2:
	{
		if (_isMaxJudge)
			m_CoolbombAnimArr[1]->Play(L"CoolbombMax", false);
		else
			m_CoolbombAnimArr[1]->Play(L"Coolbomb", false);
	}
		break;

	case GEARLINE_TYPE::_3:
	{
		if (_isMaxJudge)
			m_CoolbombAnimArr[2]->Play(L"CoolbombMax", false);
		else
			m_CoolbombAnimArr[2]->Play(L"Coolbomb", false);
	}
		break;

	case GEARLINE_TYPE::_4:
	{
		if (_isMaxJudge)
			m_CoolbombAnimArr[3]->Play(L"CoolbombMax", false);
		else
			m_CoolbombAnimArr[3]->Play(L"Coolbomb", false);
	}
		break;

	}

}
