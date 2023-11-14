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

void CCombo::ComboUp(JUDGE_VECTOR_IDX _judge)
{
	if (JUDGE_VECTOR_IDX::BREAK == _judge)
	{
		ComboBreak();
		return;
	}
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
