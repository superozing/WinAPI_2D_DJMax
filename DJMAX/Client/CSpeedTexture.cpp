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

	if (KEY_TAP(KEY::_1)) 
	{
		if (m_iSpeed != 10)
			--m_iSpeed;
	}
	if (KEY_TAP(KEY::_2)) 
	{
		if (m_iSpeed != 99)
			++m_iSpeed;
	}

#pragma endregion

}

DEFINE OFFSET_00_X = 34;
DEFINE OFFSET_00_Y = 21;

void CSpeedTexture::render(HDC _dc)
{

#pragma region _	SPEED_ICON_RENDER

	if (nullptr != m_SpeedIconBgAtlas)
	{
		int SpeedTexPrintNo = m_iSpeed / 10;
		int Speed_00_TexPrintNo = (m_iSpeed % 10) * 20;
		int renderSpeedIconX = 72 * (SpeedTexPrintNo - 1);

		Vec2 vPos = GetPos();
		Vec2 vTempPos = { 120, 690 };
		int  a = int(72 * 0.8333f + 1);
		AlphaBlend(_dc
			, vPos.x, vPos.y
			, 60, 60
			, m_SpeedIconBgAtlas->GetDC()
			, renderSpeedIconX, 0
			, 72, 72
			, m_blendFunc);

		AlphaBlend(_dc
			, vPos.x + OFFSET_00_X, vPos.y + OFFSET_00_Y
			, 17, 32
			, m_SpeedIcon_00Atlas->GetDC()
			, Speed_00_TexPrintNo, 0
			, 20, 38
			, m_blendFunc);
	}

#pragma endregion

}

