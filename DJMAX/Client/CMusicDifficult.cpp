#include "pch.h"
#include "CMusicDifficult.h"
#include "CAssetMgr.h"
#include "CTexture.h"

CMusicDifficult::CMusicDifficult()
	:m_Normal_DifficultBG(FINDTEX(L"Normal_DifficultBG"))
	,m_Normal_Difficult(FINDTEX(L"Normal_Difficult"))
	,m_SC_DifficultBG(FINDTEX(L"SC_DifficultBG"))
	,m_SC_Difficult(FINDTEX(L"SC_Difficult"))
	,m_iCulDifficult(13)
	,m_isSC(false)
	, m_blend
	{
		AC_SRC_OVER,
		0,
		255,
		AC_SRC_ALPHA
	}
{
}

CMusicDifficult::~CMusicDifficult()
{
}

void CMusicDifficult::render(HDC _dc)
{
	// SC 난이도일 경우에는 SC 텍스쳐를 출력해야 해요.
	if (m_isSC)
	{
		// nullptr check
		if (m_SC_DifficultBG && m_SC_Difficult)
		{
			Vec2 vPos = GetPos();
			Vec2 vImgScale = { m_SC_DifficultBG->GetWidth(), m_SC_DifficultBG->GetHeight() };
			AlphaBlend(_dc
				, vPos.x, vPos.y
				, vImgScale.x, vImgScale.y
				, m_SC_DifficultBG->GetDC()
				, 1, 0
				, vImgScale.x - 1, vImgScale.y
				, m_blend);

			AlphaBlend(_dc
				, vPos.x, vPos.y
				, (vImgScale.x) / 15 * m_iCulDifficult, vImgScale.y
				, m_SC_Difficult->GetDC()
				, 1, 0
				, ((vImgScale.x) / 15 * m_iCulDifficult) - 1, vImgScale.y
				, m_blend);
		}
	}

	// 기본 난이도일 경우에는 기본 텍스쳐를 출력해야 해요.
	else
	{
		// nullptr check
		if (m_Normal_DifficultBG && m_Normal_Difficult)
		{
			Vec2 vPos = GetPos();
			Vec2 vImgScale = { m_SC_DifficultBG->GetWidth(), m_SC_DifficultBG->GetHeight() };
			AlphaBlend(_dc
				, vPos.x, vPos.y
				, vImgScale.x, vImgScale.y
				, m_Normal_DifficultBG->GetDC()
				, 1, 0
				, vImgScale.x - 1, vImgScale.y
				, m_blend);

			AlphaBlend(_dc
				, vPos.x, vPos.y
				, (vImgScale.x) / 15 * m_iCulDifficult, vImgScale.y
				, m_Normal_Difficult->GetDC()
				, 1, 0
				, ((vImgScale.x) / 15 * m_iCulDifficult) - 1, vImgScale.y
				, m_blend);

		}
	}
}

void CMusicDifficult::SetDifficult(int _difficult)
{
	if (0 > _difficult)
		m_isSC = true;
	else
		m_isSC = false;
		
	m_iCulDifficult = abs(_difficult);
}
