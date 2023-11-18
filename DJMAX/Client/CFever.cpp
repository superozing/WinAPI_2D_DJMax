#include "pch.h"
#include "CFever.h"
#include "CTexture.h"
#include "CAssetMgr.h"
#include "CTimeMgr.h"
#include "CSound.h"

DEFINE FEVER_GAUGE_MAX = 1000;

CFever::CFever()
	:m_CurFeverGauge(0)
	, m_CurFeverPower(1)
	, m_FeverTriggerPercent(100)
	, m_FeverEffectSound(FINDSND(L"effect_Fever"))
	, m_FeverGearBG(FINDTEX(L"fever_bg_atlas"))
	, m_FeverGearText(FINDTEX(L"fever_sidetxt_atlas"))
	, m_FeverTextAtlas(FINDTEX(L"fever_mul_atlas"))
	, m_FeverBarBG(FINDTEX(L"fever_bar_bg"))
	, m_FeverBarAtlas(FINDTEX(L"fever_bar_atlas"))
	, m_FeverRingAtlas(FINDTEX(L"fever_ring_atlas"))
	, m_FeverTextSizePercent(.0f)
{

	m_FeverEffectSound->SetVolume(50);
}

CFever::~CFever()
{ 
}


void CFever::tick(float _DT)
{
}

void CFever::GearInsideRender(HDC _dc)
{
	static 	BLENDFUNCTION m_blend;
	m_blend.BlendOp = AC_SRC_OVER;
	m_blend.BlendFlags = 0;
	m_blend.AlphaFormat = AC_SRC_ALPHA; // 0
	m_blend.SourceConstantAlpha = 255;

	if (m_CurFeverPower != 1)
	{
		static int alpha = 255;
		static int minus = 1;

		m_blend.SourceConstantAlpha = alpha;

		AlphaBlend(_dc
			, 98, 118
			, 422, 580
			, m_FeverGearBG->GetDC()
			, 502 * (m_CurFeverPower - 2), 0
			, 502, 550
			, m_blend);

		int alphaBuf = alpha + (512 * DT * minus);

		if (alphaBuf < 0 || alphaBuf > 150)
		{
			minus *= -1;
		}

		alpha += 300 * DT * minus;
	
		m_blend.SourceConstantAlpha = 150;
		
		static float DestY[2] = { 0.f, 852.f };

		for (int i = 0; i < 2; ++i)
		{
			// 왼 쪽 텍스트
			AlphaBlend(_dc
				, 100, DestY[i]
				, 32, 852
				, m_FeverGearText->GetDC()
				, 32 * (m_CurFeverPower - 2), 0
				, 32, 852
				, m_blend);

			// 오른 쪽 텍스트
			AlphaBlend(_dc
				, 484, DestY[i]
				, 32, 852
				, m_FeverGearText->GetDC()
				, 32 * (m_CurFeverPower - 2), 0
				, 32, 852
				, m_blend);

			DestY[i] -= 300 * DT;

			if (DestY[i] < -852.f)
			{
				DestY[i] = 852.f;
			}
		}



	
	}
}

void CFever::render(HDC _dc)
{
	// 현재 설정된 m_CurFeverPower에 비례한 인덱스에 따른 애니메이션과 텍스쳐 출력
	// ***기어 중심부: x: 306***
	// 블렌드옵션... 정적으로 놔두어요.
	static 	BLENDFUNCTION m_blend;
	m_blend.BlendOp = AC_SRC_OVER;
	m_blend.BlendFlags = 0;
	m_blend.AlphaFormat = AC_SRC_ALPHA; // 0
	m_blend.SourceConstantAlpha = 255;

	// 2.
	if (m_FeverTriggerPercent != 100 && m_CurFeverPower != 1)
	{
		if (m_FeverTriggerPercent > 80.f)
		{
			m_blend.SourceConstantAlpha = m_FeverTriggerPercent * -2.5f;
		}

		m_FeverTextSizePercent = m_FeverTriggerPercent / 80;
		if (m_FeverTextSizePercent < 0.3f)  m_FeverTextSizePercent = 0.3f;
		if (m_FeverTextSizePercent > 1.f)	m_FeverTextSizePercent = 1.f;

		AlphaBlend(_dc
			, 306 - (95 * m_FeverTextSizePercent), 380 - (54 * m_FeverTextSizePercent)
			, 190 * m_FeverTextSizePercent, 107 * m_FeverTextSizePercent
			, m_FeverTextAtlas->GetDC()
			, (m_CurFeverPower - 2) * 272, 0
			, 272, 153
			, m_blend);
	}
	

	// gauge bar
#pragma region _	BAR
	AlphaBlend(_dc
		, 208, 460
		, 196, 8
		, m_FeverBarBG->GetDC()
		, 0, 0
		, 196, 8
		, m_blend);
	
	// gauge bar
	AlphaBlend(_dc
		, 306 - (54 * ((float)m_CurFeverGauge / FEVER_GAUGE_MAX)), 460
		, 108 * ((float)m_CurFeverGauge / FEVER_GAUGE_MAX), 8
		, m_FeverBarAtlas->GetDC()
		, (m_CurFeverPower - 1) * 196, 0
		, 196, 8
		, m_blend);
#pragma endregion

	// fever ring
#pragma region _	RING
	if (m_FeverTriggerPercent != 100.f && m_CurFeverPower != 1)
	{
		// 알파 값 조절
		if (m_FeverTriggerPercent < 80.f)
			m_blend.SourceConstantAlpha *= m_FeverTriggerPercent / 100.f;
		else
			m_blend.SourceConstantAlpha = m_FeverTriggerPercent * -2.5f;
		
		// 801 x 801
 		AlphaBlend(_dc
			, 300 - (400 * (m_FeverTriggerPercent / 100)), 350 - (400 * (m_FeverTriggerPercent / 100))
			, 801 * (m_FeverTriggerPercent / 100), 801 * (m_FeverTriggerPercent / 100)
			, m_FeverRingAtlas->GetDC()
			, (m_CurFeverPower - 2) * 801, 0
			, 801, 801
			, m_blend);

		m_FeverTriggerPercent += 140.f * DT;

		if (m_FeverTriggerPercent > 100.f)
		{
			m_FeverTriggerPercent = 100.f;
		}
		m_blend.SourceConstantAlpha = 255;
	}
#pragma endregion
}

void CFever::FeverPowerUp()
{
	// 증가 시켜요.
	// 이미 배율이 5일 경우에는 증가 시킬 필요 없이 그냥 fever 애니메이션만 출력 해주면 된다.
	if (5 != m_CurFeverPower)
	{
		m_CurFeverPower += 1;
	}

	// 각종 애니메이션을 출력하도록 설정하기
	m_FeverTriggerPercent = 0.f;

	// 파워가 올라갈 때 사운드도 출력하면 좋겠다.
	m_FeverEffectSound->SetPosition(0);
}

void CFever::FeverBreak()
{
	// 모든 값을 초기 상태로 바꾸기
	m_CurFeverPower = 1;
	m_CurFeverGauge = 0;
}


void CFever::FeverGaugeUp(JUDGE_VECTOR_IDX _judge)
{
	if (JUDGE_VECTOR_IDX::BREAK == _judge)
	{
		FeverBreak();
		return;
	}

	// Fever Gauge 증가
	m_CurFeverGauge += (11 - (int)_judge);

	// 100보다 높을 경우 다음 Fever로 증가 시키기.
	if (m_CurFeverGauge > FEVER_GAUGE_MAX)
	{
		FeverPowerUp();
		m_CurFeverGauge = 0;
	}

}

