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
	// ���� Fever ������ ���� �޺� �� ������ ǥ���ؿ�.
	m_CurCombo += m_FeverPower->GetFeverPower();
}

void CCombo::ComboBreak()
{
	if (m_BestCombo < m_CurCombo)
		m_BestCombo = m_CurCombo;

	m_CurCombo = 0;
}
