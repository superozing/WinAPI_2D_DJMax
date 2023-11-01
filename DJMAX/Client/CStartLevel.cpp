#include "pch.h"
#include "CStartLevel.h"

#include "CObj.h"
#include "CAssetMgr.h"
#include "CSound.h"
#include "CAnimator.h"
#include "CKeyMgr.h"

#include "CLevelChoice.h"
#include "CBtnUI.h"
#include "CBtn_start.h"

#include "CBackGround.h"
#include "CBackground_alpha.h"

#include "CIcon.h"
#include "CIcon_start.h"

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
	//ShowCursor(false);
	//ShowCursor(true);
#pragma region Background
	CBackground* pBackground = new CBackground;
	pBackground->SetTexture(FINDTEX(L"background_default"));
	AddObject(LAYER::BACK_GROUND, pBackground);

	CBackground_alpha* pBgAlpha = new CBackground_alpha;
	pBgAlpha->SetTexture(FINDTEX(L"background_shine"));
	pBgAlpha->SetAlpha(0);
	AddObject(LAYER::BACK_GROUND, pBgAlpha);

	m_pStripeBg = new CBackground;
	m_pStripeBg->SetTexture(FINDTEX(L"background_strip_square"));
	m_pStripeBg->SetAlpha(0);
	m_pStripeBg->SetMaxAlpha(65);
	AddObject(LAYER::BACK_GROUND, m_pStripeBg);
#pragma endregion

#pragma region Icon
	m_pMainIcon = new CIcon_start;
	m_pMainIcon->SetIcon(FINDTEX(L"logo_large"));
	m_pMainIcon->SetPos(Vec2(800, 450));
	m_pMainIcon->SetScale(Vec2(239, 620));
	AddObject(LAYER::WORLD_STATIC, m_pMainIcon);

#pragma endregion

#pragma region LevelBtn
	m_pSelect = new CBtn_start;
	m_pSelect->SetPos(Vec2(200, 1500));
	m_pSelect->SetScale(Vec2(500, 430));
	m_pSelect->SetNormalImg(FINDTEX(L"LevelSelectBtn_Editor_Default"));
	m_pSelect->SetHoverImg(FINDTEX(L"LevelSelectBtn_Editor_MouseOn"));
	m_pSelect->SetPressedImg(FINDTEX(L"LevelSelectBtn_Editor_MouseOn"));
	m_pSelect->SetDeletage(this, (DelegateFunc)&CStartLevel::exit);
	AddObject(LAYER::UI, m_pSelect);
	m_pEditor = m_pSelect->Clone();
	m_pEditor->SetNormalImg(FINDTEX(L"LevelSelectBtn_Select_Default"));
	m_pEditor->SetHoverImg(FINDTEX(L"LevelSelectBtn_Select_MouseOn"));
	m_pEditor->SetPressedImg(FINDTEX(L"LevelSelectBtn_Select_MouseOn"));
	m_pEditor->SetDeletage(this, (DelegateFunc)&CStartLevel::exit);
	m_pEditor->SetPos(Vec2(900,1500));
	AddObject(LAYER::UI, m_pEditor);
#pragma endregion

#pragma region Sound
	m_pBGM = FINDSND(L"mainBGM");
	m_pBGM->SetVolume(70);
	m_pBGM->SetPosition(45.f);
	m_pEffect_swoosh = FINDSND(L"effect_fast");
	m_pEffect_swoosh->SetVolume(100);
	m_pEffect_choice = FINDSND(L"effect_interface");
#pragma endregion

}

void CStartLevel::enter()
{	
	m_pBGM->Play(true);
	CCamera::GetInst()->FadeIn(1.f);
}

void CStartLevel::exit()
{
	// 포커싱 개념 넣어야 함"중요"
	m_pBGM->Stop();
	m_pEffect_choice->Play();
	CCamera::GetInst()->FadeOut(1.f);
	ChangeLevel(LEVEL_TYPE::EDITOR_LEVEL);

	DeleteAllObjects();
}


void CStartLevel::tick()
{
	CLevel::tick();

	if (KEY_TAP(KEY::SPACE))
	{
		m_pEffect_swoosh->Play();
 		m_pStripeBg->SmoothChangeAlpha(255);
		m_pMainIcon->SelectPhase();
		m_pSelect->SelectPhase();
		m_pEditor->SelectPhase();

	}


}

CStartLevel::CStartLevel()
	: m_pBGM(nullptr)
	, m_pEditor(nullptr)
	, m_pEffect_choice(nullptr)
	, m_pEffect_swoosh(nullptr)
	, m_pMainIcon(nullptr)
	, m_pSelect(nullptr)
	, m_pStripeBg(nullptr)
{

}

CStartLevel::~CStartLevel()
{
}
