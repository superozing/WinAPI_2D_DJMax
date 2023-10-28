#include "pch.h"
#include "CLevelChoice.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CLevelMgr.h"
#include "CLevel.h"

#include "CPathMgr.h"
#include "CEngine.h"

#include "CAssetMgr.h"
#include "CTexture.h"
#include "CLogMgr.h"

#include "components.h"

CLevelChoice::CLevelChoice()
	: m_NormalImg(nullptr)
	, m_HoverAnimator(nullptr)
	, m_isAnim(true)
{	
	// 에셋 매니저로부터 텍스쳐
	m_NormalImg = CAssetMgr::GetInst()->LoadTexture(L"LevelChoice_NormalImg", L"texture\\outgame\\OnlineModeSelect.png");
	m_HoverAnimator = AddComponent<CAnimator>();
	// m_HoverAnimator는 레벨 차원에서 동적 할당 하고 값 넣어주는게 좋을 듯
}

CLevelChoice::~CLevelChoice()
{
}

void CLevelChoice::tick(float _DT)
{
	Super::tick(_DT);
}

void CLevelChoice::render(HDC _dc)
{

	Super::render(_dc);

}

void CLevelChoice::OnHovered(Vec2 _vMousePos)
{
}

void CLevelChoice::OnUnHovered(Vec2 _vMousePos)
{
}
