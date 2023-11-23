#include "pch.h"
#include "CFocusUI.h"
#include "CAssetMgr.h"
#include "CTexture.h"
#include "CMusicSelectBar.h"
#include "CMusicInfo.h"


CFocusUI::CFocusUI(class CMusicInfo* _pOwnerInfo)
	:m_pOwnerBar(nullptr)
	, m_pOwnerInfo(_pOwnerInfo)
{
	SetScale(Vec2(925, 72));
}

CFocusUI::CFocusUI(const CFocusUI& _Origin)
	:m_pOwnerBar(_Origin.m_pOwnerBar)
{
}

CFocusUI::~CFocusUI()
{
}

void CFocusUI::LBtnClicked(Vec2 _vMousePos)
{
	m_pOwnerInfo->SetMusicInfoIdx(m_pOwnerBar->GetInfoIndex());
}


void CFocusUI::render(HDC _dc)
{
	// 기존 버튼UI 와는 다른 동작을 해야 한다.
	// 예를 들어 현재 포커싱 상태에 따라서 다른 모습을 내보내야 하는 것 말이죠?
	

	if (m_PressedImg && m_NormalImg)
	{
		Vec2 vPos	= GetPos();
		Vec2 vImgScale = Vec2((float)m_NormalImg->GetWidth(), (float)m_NormalImg->GetHeight());

		m_blendFunc.SourceConstantAlpha = 255;

		AlphaBlend(_dc
			, int(vPos.x), int(vPos.y) 
			, 925, 72
			, m_NormalImg->GetDC()
			, 0, 0
			, int(vImgScale.x), int(vImgScale.y)
			, m_blendFunc);

		if (m_pOwnerBar->GetBlendFunction().SourceConstantAlpha != 0)
		{
			AlphaBlend(_dc
				, int(vPos.x), int(vPos.y)
				, 925, 72
				, m_PressedImg->GetDC()
				, 0, 0
				, int(vImgScale.x), int(vImgScale.y)
				, m_pOwnerBar->GetBlendFunction());
		}
	}

	CUI::render(_dc);

}

