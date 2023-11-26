#include "pch.h"
#include "CPause.h"
#include "CBtnUI.h"
#include "CAssetMgr.h"
#include "CStringTexture.h"
#include "CPlayLevel.h"
#include "CGear_playlevel.h"

void ChangeSelectLevelCallback1() { ChangeLevel(LEVEL_TYPE::SELECT_LEVEL); }


CPause::CPause(CPlayLevel* pOwnerLevel)
	: m_pOwner(pOwnerLevel)
{
	m_PauseTxt = new CStringTexture;
	m_PauseTxt->SetTexture(FINDTEX(L"Pause_txt"));
	m_PauseTxt->SetPos(Vec2(820, 110));
	m_PauseTxt->SetScale(Vec2(457, 125));

	m_ContinueBtn	= new CBtnUI;
	m_RestartBtn	= new CBtnUI;
	m_ExitBtn		= new CBtnUI;

	m_ContinueBtn->SetNormalImg(FINDTEX(L"continue_unhover"));
	m_ContinueBtn->SetHoverImg(FINDTEX(L"continue_hover"));

	m_RestartBtn->SetNormalImg(FINDTEX(L"restart_unhover"));
	m_RestartBtn->SetHoverImg(FINDTEX(L"restart_hover"));

	m_ExitBtn->SetNormalImg(FINDTEX(L"musicselect_unhover"));
	m_ExitBtn->SetHoverImg(FINDTEX(L"musicselect_hover"));

	m_ContinueBtn->SetPos(Vec2(760, 350)); // 590 67
	m_RestartBtn->SetPos(Vec2(760, 450));
	m_ExitBtn->SetPos(Vec2(760, 550));	

	m_ContinueBtn->SetScale(Vec2(590, 67)); // 590 67
	m_RestartBtn->SetScale(Vec2(590, 67));
	m_ExitBtn->SetScale(Vec2(590, 67));

	m_ContinueBtn->SetDeletage((CEntity*)m_pOwner->m_pGear, (DelegateFunc)&CGear_PlayLevel::PlayMusic);
	m_RestartBtn->SetDeletage((CEntity*)m_pOwner->m_pGear, (DelegateFunc)&CGear_PlayLevel::PlayMusic);
	m_ExitBtn->SetCallBack(ChangeSelectLevelCallback1);

	pOwnerLevel->AddObject(LAYER::UI, m_ContinueBtn);
	pOwnerLevel->AddObject(LAYER::UI, m_RestartBtn);
	pOwnerLevel->AddObject(LAYER::UI, m_ExitBtn);
}

CPause::~CPause()
{
	delete m_PauseTxt;
}

void CPause::tick(float _DT)
{

}

void CPause::render(HDC _dc)
{
	m_PauseTxt->render(_dc);
}


