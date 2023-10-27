#pragma once

class CUI;

class CUIMgr
{
	SINGLETON(CUIMgr);
private:
	// 최상위 UI들 중 포커싱 중인 UI
	CUI* m_FocuedUI;

public:
	void tick();

private:
	CUI* GetPriorityCheck(CUI* _ParentUI);
};

