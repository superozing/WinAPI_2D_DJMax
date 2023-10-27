#include "pch.h"
#include "CLogMgr.h"

#include "CTimeMgr.h"

CLogMgr::CLogMgr()
	: m_LogMaxLife(5.f) // 기본 5초
{
}

CLogMgr::~CLogMgr()
{
}

void CLogMgr::tick(HDC _dc)
{
	list<FLog>::iterator iter = m_LogList.begin();

	// 모든 로그에 DT만큼 시간이 흘러요
	for (; iter != m_LogList.end(); )
	{
		(*iter).AccTime += DT;
		if (m_LogMaxLife < (*iter).AccTime)
		{
			iter = m_LogList.erase(iter);
		}
		else
		{
			++iter;
		}
	}

	iter = m_LogList.begin();
	POINT LT = { 10, 10 }; // 너무 딱 붙어있지 않도록 LeftTop 위치 => (10, 10)

	int i = 0;
	for (; iter != m_LogList.end(); ++iter, ++i)
	{
		switch ((*iter).Level)
		{
		case LOG:
			SetTextColor(_dc, RGB(0, 0, 0)); // 펜을 쓰는게 아니래요. main DC에 내보낼 텍스트 색을 직접 지정해주어요.
			TextOut(_dc, LT.x, LT.y + i * int(10.f * 1.5f), (*iter).Message.c_str(), (int)(*iter).Message.length());
			break;
		case WARNING:
			SetTextColor(_dc, RGB(210, 210, 153));
			break;
		case ERR:
			SetTextColor(_dc, RGB(255, 0, 0));
			break;
		}

		TextOut(_dc, LT.x, LT.y + i * int(10.f * 1.5f), (*iter).Message.c_str(), (int)(*iter).Message.length());
	}
}
