#include "pch.h"
#include "CTimeMgr.h"
#include "CEngine.h"

CTimeMgr::CTimeMgr()
	:m_Frequency{}
	,m_PrevCount{}
	,m_CurCount{}
	,m_DeltaTime(.0f)
	,m_fAccTime(.0f)
	,m_iCallCount(0)
{

}

CTimeMgr::~CTimeMgr()
{
}


void CTimeMgr::init()
{
	// Frequency -> �ʴ� ��
	QueryPerformanceFrequency(&m_Frequency);

	QueryPerformanceCounter(&m_PrevCount);
}

void CTimeMgr::tick()
{
	QueryPerformanceCounter(&m_CurCount); 
	
	// DT
	m_DeltaTime = (float)(m_CurCount.QuadPart - m_PrevCount.QuadPart) / (float)(m_Frequency.QuadPart);
	m_PrevCount = m_CurCount;

	// DT ����
	if (MIN_DT < m_DeltaTime)
		m_DeltaTime = MIN_DT;
	
	// Frame üũ
	m_fAccTime += m_DeltaTime;

	if (1.f <= m_fAccTime)
	{
		wchar_t szText[50] = {};
		swprintf_s(szText, 50, L"DeltaTime : %f, FPS : %d", m_DeltaTime, m_iCallCount);
		SetWindowText(CEngine::GetInst()->GetMainWind(), szText);

		m_iCallCount = 0;
		m_fAccTime = .0f;
	}



	++m_iCallCount;
}
