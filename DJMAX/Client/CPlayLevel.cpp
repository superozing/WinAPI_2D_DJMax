#include "pch.h"
#include "CPlayLevel.h"

#include "CEngine.h"
#include "CCamera.h"
#include "CCollisionMgr.h"

#include "CKeyMgr.h"
#include "CLevelMgr.h"
#include "CAssetMgr.h"
#include "CSound.h"
#include "CBackground.h"
#include "CGear.h"

void CPlayLevel::init()
{
#pragma region Background
	CBackground* pDefaultBg = new CBackground;
	pDefaultBg->SetTexture(FINDTEX(L"bga_off_bg"));
	AddObject(LAYER::BACK_GROUND, pDefaultBg);


#pragma endregion
#pragma region gear
	m_pGear = new CGear;


	AddObject(LAYER::GEAR, m_pGear);

#pragma endregion


}

void CPlayLevel::enter()
{
	CCamera::GetInst()->FadeIn(1.f);

	m_pGear->LoadNoteData();

	//m_pGear->SaveNoteData();
	m_pGear->m_pMusic = FINDSND(L"music1");
	m_pGear->m_pMusic->SetVolume(70);
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
