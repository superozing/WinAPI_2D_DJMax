#include "pch.h"
#include "CCoolbomb.h"
#include "CAnimator.h"

CCoolbomb::CCoolbomb()
	:m_CoolbombAnimArr{}
{
	//for (int i = 0; i < 4; ++i)
	//{
	//	m_CoolbombAnimArr[i] = AddComponent<CAnimator>(L"CoolBomb");
	//	m_CoolbombAnimArr[i]->
	//}



}

CCoolbomb::~CCoolbomb()
{
}


void CCoolbomb::tick(float _DT)
{
}

void CCoolbomb::render(HDC _dc)
{
}

void CCoolbomb::SetCoolbombAnimation(GEARLINE_TYPE _line, bool _isMaxJudge)
{
}
