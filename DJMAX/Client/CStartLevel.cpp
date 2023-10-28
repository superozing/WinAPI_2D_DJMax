#include "pch.h"
#include "CStartLevel.h"

#include "CObj.h"
#include "CAssetMgr.h"

#include "CAnimator.h"

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
}

void CStartLevel::enter()
{
	CBtnUI* pLevelSelectBtn = new CBtnUI;
	pLevelSelectBtn->SetPos(Vec2(400, 450));
	pLevelSelectBtn->SetScale(Vec2(500, 430));
	pLevelSelectBtn->SetNormalImg(CAssetMgr::GetInst()->LoadTexture(L"이미지1", L"texture\\ModeSelect1.png"));
	pLevelSelectBtn->SetHoverImg(CAssetMgr::GetInst()->LoadTexture(L"이미지2", L"texture\\1-cutout.png"));
	pLevelSelectBtn->SetPressedImg(CAssetMgr::GetInst()->LoadTexture(L"이미지3", L"texture\\1-cutout.png"));
	AddObject(LAYER::UI, pLevelSelectBtn);
	pLevelSelectBtn = pLevelSelectBtn->Clone();
	pLevelSelectBtn->SetNormalImg(CAssetMgr::GetInst()->LoadTexture(L"이미지4", L"texture\\ModeSelect2.png"));
	pLevelSelectBtn->SetHoverImg(CAssetMgr::GetInst()->LoadTexture(L"이미지5", L"texture\\2-cutout.png"));
	pLevelSelectBtn->SetPressedImg(CAssetMgr::GetInst()->LoadTexture(L"이미지6", L"texture\\2-cutout.png"));
	pLevelSelectBtn->SetPos(Vec2(1200,450));
	AddObject(LAYER::UI, pLevelSelectBtn);

}

void CStartLevel::exit()
{
	DeleteAllObjects();

}

void CStartLevel::tick()
{
	CLevel::tick();

}
