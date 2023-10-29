#include "pch.h"
#include "CStartLevel.h"

#include "CObj.h"
#include "CAssetMgr.h"
#include "CSound.h"
#include "CAnimator.h"
#include "CKeyMgr.h"

#include "CLevelChoice.h"
#include "CBtnUI.h"

/* 오브젝트
* 1. 오브젝트
*	버튼UI 2개
*	
* 



*/

void CStartLevel::init()
{
	CBtnUI* pLevelSelectBtn = new CBtnUI;
	pLevelSelectBtn->SetPos(Vec2(0, 100));
	pLevelSelectBtn->SetScale(Vec2(500, 430));
	pLevelSelectBtn->SetNormalImg(CAssetMgr::GetInst()->LoadTexture(L"이미지1", L"texture\\ModeSelect1.png"));
	pLevelSelectBtn->SetHoverImg(CAssetMgr::GetInst()->LoadTexture(L"이미지2", L"texture\\2-cutout.png"));
	pLevelSelectBtn->SetPressedImg(CAssetMgr::GetInst()->LoadTexture(L"이미지3", L"texture\\2-cutout.png"));
	AddObject(LAYER::UI, pLevelSelectBtn);
	pLevelSelectBtn = pLevelSelectBtn->Clone();
	pLevelSelectBtn->SetNormalImg(CAssetMgr::GetInst()->LoadTexture(L"이미지4", L"texture\\ModeSelect2.png"));
	pLevelSelectBtn->SetHoverImg(CAssetMgr::GetInst()->LoadTexture(L"이미지5", L"texture\\1-cutout.png"));
	pLevelSelectBtn->SetPressedImg(CAssetMgr::GetInst()->LoadTexture(L"이미지6", L"texture\\1-cutout.png"));
	pLevelSelectBtn->SetPos(Vec2(800,100));
	AddObject(LAYER::UI, pLevelSelectBtn);
}

void CStartLevel::enter()
{	
	CSound* pSound = CAssetMgr::GetInst()->LoadSound(L"BGM_01", L"sound\\DM.wav");
	pSound->SetVolume(100);
	pSound->SetPosition(45.f);
	pSound->Play(true);

}

void CStartLevel::exit()
{
	DeleteAllObjects();

}


void CStartLevel::tick()
{
	CLevel::tick();
	// Enter 키가 눌리면 다른 레벨로 변환
	if (KEY_TAP(KEY::ENTER))
	{
		ChangeLevel(LEVEL_TYPE::EDITOR_LEVEL);
	}
}
