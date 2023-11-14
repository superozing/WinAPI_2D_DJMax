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
	// 현재 설정된 m_CurFeverPower에 비례한 인덱스에 따른 애니메이션과 텍스쳐 출력
	
	// 원 색도 바뀌어야 하고...
	// 바 색도 바뀌어야 하고...
	// 배율 색도
	// 텍스트 색도...
	// 배경 색도...

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


}

void CFever::FeverBreak()
{
	// 모든 값을 초기 상태로 바꾸기
	m_CurFeverPower = 1;
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
	if (m_CurFeverGauge > 100)
	{
		FeverPowerUp();
		m_CurFeverGauge = 0;
	}

}

