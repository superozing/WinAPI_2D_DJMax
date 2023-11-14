#include "pch.h"
#include "CCombo.h"

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
	m_CurCombo += m_FeverPower->GetFeverPower();
}

void CCombo::ComboBreak()
{
	if (m_BestCombo < m_CurCombo)
		m_BestCombo = m_CurCombo;

	m_CurCombo = 0;
}
