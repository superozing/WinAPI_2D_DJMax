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
	// ���� Fever ������ ���� �޺� �� ������ ǥ���ؿ�.
	if (m_FeverPower != nullptr)
		m_CurCombo += m_FeverPower->GetFeverPower();
	else
		LOG(LOG_LEVEL::ERR, L"Combo ���� Fever �����Ͱ� nullptr�Դϴ�.");
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
