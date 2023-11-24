#include "pch.h"
#include "CSpeedTexture.h"
#include "CTexture.h"
#include "CAssetMgr.h"
#include "CKeyMgr.h"

CSpeedTexture::CSpeedTexture()
	:m_blendFunc
	{ 
		AC_SRC_OVER
		, 0
		, 255
		, AC_SRC_ALPHA 
	}
	,m_iSpeed(10)
	,m_SpeedIconBgAtlas(FINDTEX(L"icon_speed_atlas"))
	,m_SpeedIcon_00Atlas(FINDTEX(L"icon_speed_00_atlas"))
{
}

CSpeedTexture::~CSpeedTexture()
{
}

void CSpeedTexture::tick(float _DT)
{

#pragma region _	SPEED CHECK

	if (KEY_TAP(KEY::_1)) --m_iSpeed;
	if (KEY_TAP(KEY::_2)) ++m_iSpeed;

#pragma endregion

}

void CSpeedTexture::render(HDC _dc)
{

#pragma region _	SPEED_ICON_RENDER

	if (nullptr != m_SpeedIconBgAtlas)
	{
		int SpeedTexPrintNo = m_iSpeed / 10;
		int Speed_00_TexPrintNo = (m_iSpeed % 10) * 20;
		int renderSpeedIconX = 72 * (SpeedTexPrintNo - 1);

		AlphaBlend(_dc
			, 120, 690
			, int(72 * 0.8333f + 1), int(72 * 0.8333f + 1)
			, m_SpeedIconBgAtlas->GetDC()
			, renderSpeedIconX, 0
			, 72, 72
			, m_blendFunc);

		AlphaBlend(_dc
			, 154, 711
			, int(20 * 0.8333f + 1), int(38 * 0.8333f + 1)
			, m_SpeedIcon_00Atlas->GetDC()
			, Speed_00_TexPrintNo, 0
			, 20, 38
			, m_blendFunc);
	}

#pragma endregion

}

