#include "pch.h"
#include "CPlayLevel.h"

#include "CEngine.h"
#include "CCamera.h"
#include "CCollisionMgr.h"

#include "CKeyMgr.h"
#include "CPathMgr.h"
#include "CLevelMgr.h"
#include "CAssetMgr.h"
#include "CSound.h"
#include "CBackground.h"
#include "CGear_PlayLevel.h"
#include "CBGA.h"
#include "CJudgeTexture.h"
#include "CLineShine.h"
#include "CCoolbomb.h"
#include "CCombo.h"
#include "CFever.h"

void CPlayLevel::init() 
{
#pragma region BG
	CBackground* pDefaultBg = new CBackground;
	pDefaultBg->SetTexture(FINDTEX(L"bga_off_bg"));
	AddObject(LAYER::BACK_GROUND, pDefaultBg);

	//wstring strContentPath = CPathMgr::GetContentPath();
	//wstring strFilePath = strContentPath + L"Video\\MICDROP.mp4";
	//CBGA* pBGA = new CBGA(strFilePath.c_str());
	//AddObject(LAYER::BACK_GROUND, pBGA); // 왜 안되는거야..............

#pragma endregion

#pragma region TEXTURE_ALLOC

	m_JudgeTex = new CJudgeTexture;
	AddObject(LAYER::JUDGE, m_JudgeTex);

	m_LineTex = new CLineShine;
	AddObject(LAYER::SHINE, m_LineTex);

	m_CoolbombTex = new CCoolbomb;
	AddObject(LAYER::COOLBOMB, m_CoolbombTex);

	m_Combo = new CCombo;
	AddObject(LAYER::COMBO, m_Combo);

	m_Fever = new CFever;
	AddObject(LAYER::FEVER, m_Fever);

#pragma endregion

#pragma region GEAR
	GetVecJudge()->resize((UINT)JUDGE_VECTOR_IDX::END, 0); // 모든 판정 들을 0으로 설정해주어요.
	m_pGear = new CGear_PlayLevel(GetVecJudge(), m_JudgeTex, m_LineTex, m_CoolbombTex, m_Combo, m_Fever);
	AddObject(LAYER::GEAR, m_pGear);
#pragma endregion


#pragma region TEXTURE_INIT
	m_LineTex->SetOwnerGear(m_pGear);
	m_JudgeTex->SetPos(Vec2(260, 500));
	m_JudgeTex->SetOwnerGear(m_pGear);
	m_Combo->SetFeverPointer(m_Fever);
#pragma endregion


}

void CPlayLevel::enter()
{
	CCamera::GetInst()->FadeIn(1.f);

	m_pGear->LoadNoteData();
	m_pGear->m_pOwnerLevel = this;

	// 음악 설정 (나중에 여러 개의 음악을 넣어야 할 때가 생길텐데... 이 때 이 부분을 수정해주어야 한다.)
	m_pGear->m_pMusic = FINDSND(L"music1");
	m_pGear->m_pMusic->SetVolume(50);
	m_pGear->m_pMusic->SetPosition(0.f);
	m_pGear->m_pMusic->Play();


}

void CPlayLevel::exit()
{
	CCamera::GetInst()->FadeOut(0.3f);
	DeleteAllObjects();

}

void CPlayLevel::tick()
{
	CLevel::tick();
}
