#include "pch.h"
#include "CStartLevel.h"

#include "CObj.h"
#include "CAssetMgr.h"
#include "CSound.h"
#include "CAnimator.h"
#include "CKeyMgr.h"

#include "CLevelChoice.h"
#include "CBtnUI.h"
#include "CBackGround.h"

#pragma region MyRegion
// 이러면 영역 저장이 가능해진다. 기능이 이게 끝인 신박한 매크로
#pragma endregion



/* 오브젝트
* 1. 오브젝트
*	버튼UI 2개
*	
* 



*/

	// 버튼 UI를 상속 받는 새로운 오브젝트의 정의가 필요해 보여요.

	// 코드가 너무 길어지는데.. 아예 버튼 UI에 새로운 생성자를 하나 만들어서 사용하는 건 어떨까.
	// 텍스쳐 키 값을 인자로 넣어주면 FINDTEX를 자동으로 생성자 쪽에서 자동으로 호출해주면 될 것 같은데.
	// 어차피 FindTexture 함수 내부에서는 값을 찾지 못했을 경우에 nullptr을 반환하니까 
	// 만약 키 값이 잘못되었을 경우에는 로그 하나 띄워주고 자동으로 nullptr이 들어가니까 알파블렌딩 시도도 안하고 검은 사각형 출력 할 듯.
	// 


void CStartLevel::init()
{
	ShowCursor(false);
	ShowCursor(true);
#pragma region Background
	CBackground* pBackground = new CBackground;
	pBackground->SetTexture(FINDTEX(L"background_default"));
	AddObject(LAYER::BACK_GROUND, pBackground);
	m_pStripeBg = new CBackground;
	m_pStripeBg->SetTexture(FINDTEX(L"background_strip"));
	AddObject(LAYER::BACK_GROUND, m_pStripeBg);

#pragma endregion

#pragma region Icon

#pragma endregion

#pragma region LevelBtn
	CBtnUI* pLevelSelectBtn = new CBtnUI;
	pLevelSelectBtn->SetPos(Vec2(0, 100));
	pLevelSelectBtn->SetScale(Vec2(500, 430));
	pLevelSelectBtn->SetNormalImg(FINDTEX(L"LevelSelectBtn_Editor_Default"));
	pLevelSelectBtn->SetHoverImg(FINDTEX(L"LevelSelectBtn_Editor_MouseOn"));
	pLevelSelectBtn->SetPressedImg(FINDTEX(L"LevelSelectBtn_Editor_MouseOn"));
	AddObject(LAYER::UI, pLevelSelectBtn);
	pLevelSelectBtn = pLevelSelectBtn->Clone();
	pLevelSelectBtn->SetNormalImg(FINDTEX(L"LevelSelectBtn_Select_Default"));
	pLevelSelectBtn->SetHoverImg(FINDTEX(L"LevelSelectBtn_Select_MouseOn"));
	pLevelSelectBtn->SetPressedImg(FINDTEX(L"LevelSelectBtn_Select_MouseOn"));
	pLevelSelectBtn->SetPos(Vec2(800,100));
	AddObject(LAYER::UI, pLevelSelectBtn);
#pragma endregion

#pragma region MainBGM
	m_pBGM = FINDSND(L"mainBGM");
	m_pBGM->SetVolume(70);
	m_pBGM->SetPosition(45.f);
#pragma endregion

}

void CStartLevel::enter()
{	
	m_pBGM->Play(true);
}

void CStartLevel::exit()
{
	// ScoreLevel로 넘어갈 때, 점수와 게임 결과를 넘겨주는게 좋아보임.

	DeleteAllObjects();

}


void CStartLevel::tick()
{
	CLevel::tick();

	if (KEY_TAP(KEY::C))
	{
		
	}


	// Enter 키가 눌리면 다른 레벨로 변환
	if (KEY_TAP(KEY::ENTER))
	{
		// 포커싱 개념 넣어야 함"중요"
		if()
		m_pStripeBg->SmoothChangeAlpha(255);
		ChangeLevel(LEVEL_TYPE::EDITOR_LEVEL);
	}
}
