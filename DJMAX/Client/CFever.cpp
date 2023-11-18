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
			// �� �� �ؽ�Ʈ
			AlphaBlend(_dc
				, 100, DestY[i]
				, 32, 852
				, m_FeverGearText->GetDC()
				, 32 * (m_CurFeverPower - 2), 0
				, 32, 852
				, m_blend);

			// ���� �� �ؽ�Ʈ
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
	// ���� ������ m_CurFeverPower�� ����� �ε����� ���� �ִϸ��̼ǰ� �ؽ��� ���
	// ***��� �߽ɺ�: x: 306***
	// ����ɼ�... �������� ���ξ��.
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
		// ���� �� ����
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
	// ���� ���ѿ�.
	// �̹� ������ 5�� ��쿡�� ���� ��ų �ʿ� ���� �׳� fever �ִϸ��̼Ǹ� ��� ���ָ� �ȴ�.
	if (5 != m_CurFeverPower)
	{
		m_CurFeverPower += 1;
	}

	// ���� �ִϸ��̼��� ����ϵ��� �����ϱ�
	m_FeverTriggerPercent = 0.f;

	// �Ŀ��� �ö� �� ���嵵 ����ϸ� ���ڴ�.
	m_FeverEffectSound->SetPosition(0);
}

void CFever::FeverBreak()
{
	// ��� ���� �ʱ� ���·� �ٲٱ�
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

	// Fever Gauge ����
	m_CurFeverGauge += (11 - (int)_judge);

	// 100���� ���� ��� ���� Fever�� ���� ��Ű��.
	if (m_CurFeverGauge > FEVER_GAUGE_MAX)
	{
		FeverPowerUp();
		m_CurFeverGauge = 0;
	}

}

