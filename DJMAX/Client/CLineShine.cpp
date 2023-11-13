#include "pch.h"
#include "CLineShine.h"


#include "CLogMgr.h"
#include "CAssetMgr.h"
#include "CTexture.h"

CLineShine::CLineShine()
	:m_ButtonTex{}
	,m_LineTex{}
{
	for (int i = 0; i < 4; ++i)
	{
		m_ButtonTex[i] = new ShineTex;
		m_ButtonTex[i]->alpha = 255;
		m_ButtonTex[i]->isRender = false;
		m_LineTex[i] = new ShineTex;
		m_LineTex[i]->alpha = 255;
		m_LineTex[i]->isRender = false;
	}
	m_ButtonTex[0]->pShineTex = FINDTEX(L"gear_btn_hit_white");
	m_ButtonTex[1]->pShineTex = FINDTEX(L"gear_btn_hit_blue");
	m_ButtonTex[2]->pShineTex = FINDTEX(L"gear_btn_hit_blue");
	m_ButtonTex[3]->pShineTex = FINDTEX(L"gear_btn_hit_white");
	
	m_LineTex[0]->pShineTex = FINDTEX(L"gear_whiteline_click");
	m_LineTex[1]->pShineTex = FINDTEX(L"gear_blueline_click");
	m_LineTex[2]->pShineTex = FINDTEX(L"gear_blueline_click");
	m_LineTex[3]->pShineTex = FINDTEX(L"gear_whiteline_click");
}

CLineShine::~CLineShine()
{
	for (int i = 0; i < 4; ++i)
	{
		delete m_LineTex[i];
		delete m_ButtonTex[i];
	}
}

void CLineShine::SetShineOn(GEARLINE_TYPE _ShineLine)
{
	if (_ShineLine == GEARLINE_TYPE::LEFTSIDE || _ShineLine == GEARLINE_TYPE::RIGHTSIDE)
		return;

	switch (_ShineLine)
	{
	case GEARLINE_TYPE::_1:
		m_ButtonTex[0]->isRender = true;
		m_LineTex[0]->isRender = true;
		break;
	case GEARLINE_TYPE::_2:
		m_ButtonTex[1]->isRender = true;
		m_LineTex[1]->isRender = true;
		break;
	case GEARLINE_TYPE::_3:
		m_ButtonTex[2]->isRender = true;
		m_LineTex[2]->isRender = true;
		break;
	case GEARLINE_TYPE::_4:
		m_ButtonTex[3]->isRender = true;
		m_LineTex[3]->isRender = true;
		break;
	default:
		LOG(LOG_LEVEL::ERR, L"잘못된 shine texture 설정");
		break;
	}
}

void CLineShine::SetShineOff(GEARLINE_TYPE _ShineLine)
{
	if (_ShineLine == GEARLINE_TYPE::LEFTSIDE || _ShineLine == GEARLINE_TYPE::RIGHTSIDE)
		return;

	switch (_ShineLine)
	{
	case GEARLINE_TYPE::_1:
		m_ButtonTex[0]->isRender = false;
		m_LineTex[0]->isRender = false;
		break;
	case GEARLINE_TYPE::_2:
		m_ButtonTex[1]->isRender = false;
		m_LineTex[1]->isRender = false;
		break;
	case GEARLINE_TYPE::_3:
		m_ButtonTex[2]->isRender = false;
		m_LineTex[2]->isRender = false;
		break;
	case GEARLINE_TYPE::_4:
		m_ButtonTex[3]->isRender = false;
		m_LineTex[3]->isRender = false;
		break;
	default:
		LOG(LOG_LEVEL::ERR, L"잘못된 shine texture 설정");
		break;
	}
}

void CLineShine::render(HDC _dc)
{
	BLENDFUNCTION blend;
	blend.BlendOp = AC_SRC_OVER;
	blend.BlendFlags = 0;
	blend.AlphaFormat = AC_SRC_ALPHA; // 0
	blend.SourceConstantAlpha = 255;
	for (int i = 0; i < 4; ++i)
	{
		if (m_ButtonTex[i]->isRender)
		{
			if (nullptr != m_ButtonTex[i]->pShineTex)
			{
				blend.SourceConstantAlpha = m_ButtonTex[i]->alpha;
				POINT vImgScale = { (int)m_ButtonTex[i]->pShineTex->GetWidth(), (int)m_ButtonTex[i]->pShineTex->GetHeight() };
				AlphaBlend(_dc
					, 86 +  100 * i, 674
					, 176 * 0.8333, 176 * 0.8333
					, m_ButtonTex[i]->pShineTex->GetDC()
					, 0, 0
					, vImgScale.x, vImgScale.y
					, blend);
			}
		}
	}
	//for (int i = 0; i < 4; ++i)
	//{
	//	if (m_LineTex[i]->isRender)
	//	{
	//		blend.SourceConstantAlpha = m_LineTex[i]->alpha;
	//		POINT vImgScale = { (int)m_LineTex[i]->pShineTex->GetWidth(), (int)m_LineTex[i]->pShineTex->GetHeight() };
	//		AlphaBlend(_dc
	//			, 109 + 100 * i, 18
	//			, 100, 678
	//			, m_LineTex[i]->pShineTex->GetDC()
	//			, 0, 0
	//			, vImgScale.x, vImgScale.y
	//			, blend);
	//	}
	//}


	CObj::render(_dc);
}