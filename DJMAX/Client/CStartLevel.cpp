#include "pch.h"
#include "CStartLevel.h"

#include "CObj.h"
#include "CAssetMgr.h"

#include "CAnimator.h"

#include "CLevelChoice.h"


void CStartLevel::init()
{
}

void CStartLevel::enter()
{
	// 레벨 선택지 추가
	CLevelChoice* pLevelChoice1 = new CLevelChoice;
	pLevelChoice1->AddComponent<CAnimator>(L"Animator");
	CLevelChoice* pLevelChoice2 = new CLevelChoice;
	pLevelChoice1->AddComponent<CAnimator>(L"Animator");
	CTexture* pAtlas = CAssetMgr::GetInst()->LoadTexture(L"PlayerAtlas", L"texture\\outgame\\Video\\levelchoice_atlas1.png");
	pLevelChoice1->m_HoverAnimator->CreateAnimation(L"video1", pAtlas, Vec2(0.f, 0.f), Vec2(700.f, 700.f), Vec2(0.f, 0.f), (float)1 / 60, 120);
	pAtlas = CAssetMgr::GetInst()->LoadTexture(L"PlayerAtlas", L"texture\\outgame\\Video\\levelchoice_atlas2.png");
	pLevelChoice2->m_HoverAnimator->CreateAnimation(L"video2", pAtlas, Vec2(0.f, 0.f), Vec2(700.f, 700.f), Vec2(0.f, 0.f), (float)1 / 60, 300, 20, 15);
	pLevelChoice1->SetPos(Vec2(400, 450));
	pLevelChoice2->SetPos(Vec2(1200, 450));	
	AddObject(WORLD_STATIC, pLevelChoice1);
	AddObject(WORLD_STATIC, pLevelChoice2);

	pLevelChoice1->m_HoverAnimator->Play(L"video1", true);
	pLevelChoice2->m_HoverAnimator->Play(L"video2", true);

}

void CStartLevel::exit()
{
	DeleteAllObjects();

}

void CStartLevel::tick()
{
	CLevel::tick();

}
