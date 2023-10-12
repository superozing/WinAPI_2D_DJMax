#pragma once

class CTimeMgr
{
	SINGLETON(CTimeMgr);
private: // DT
	
	LARGE_INTEGER	m_Frequency;
	LARGE_INTEGER	m_PrevCount;
	LARGE_INTEGER	m_CurCount;

	float			m_DeltaTime;


private: // frame 

	UINT			m_iCallCount;
	float			m_fAccTime;


public:
	float GetDeltaTime() { return m_DeltaTime; }

public:
	void init();
	void tick();
};

