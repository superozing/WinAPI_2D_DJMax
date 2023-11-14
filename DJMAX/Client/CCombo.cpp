#include "pch.h"
#include "CCombo.h"

#include "CLogMgr.h"

#include "CFever.h"

void CCombo::tick(float _DT)
{
}

void CCombo::render(HDC _dc)
{
}

void CCombo::ComboUp()
{
	// 현재 Fever 배율에 따른 콤보 수 증가를 표현해요.
	if (m_FeverPower != nullptr)
		m_CurCombo += m_FeverPower->GetFeverPower();
	else
		LOG(LOG_LEVEL::ERR, L"Combo 쪽의 Fever 포인터가 nullptr입니다.");
}

void CCombo::ComboBreak()
{
	if (m_BestCombo < m_CurCombo)
		m_BestCombo = m_CurCombo;

	m_CurCombo = 0;
}

CCombo::CCombo()
	:m_CurCombo(0)
	,m_BestCombo(0)
	,m_FeverPower()
{
}

CCombo::~CCombo()
{
}
