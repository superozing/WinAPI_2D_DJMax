#include "pch.h"
#include "CFever.h"


CFever::CFever()
	:m_CurFeverGauge(0)
	,m_CurFeverPower(1)
{
}

CFever::~CFever()
{
}


void CFever::tick(float _DT)
{
}

void CFever::render(HDC _dc)
{
	// ���� ������ m_CurFeverPower�� ����� �ε����� ���� �ִϸ��̼ǰ� �ؽ��� ���
	
	// �� ���� �ٲ��� �ϰ�...
	// �� ���� �ٲ��� �ϰ�...
	// ���� ����
	// �ؽ�Ʈ ����...
	// ��� ����...

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


}

void CFever::FeverBreak()
{
	// ��� ���� �ʱ� ���·� �ٲٱ�
	m_CurFeverPower = 1;
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
	if (m_CurFeverGauge > 100)
	{
		FeverPowerUp();
		m_CurFeverGauge = 0;
	}

}

