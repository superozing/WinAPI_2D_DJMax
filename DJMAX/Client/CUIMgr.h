#pragma once

class CUI;

class CUIMgr
{
	SINGLETON(CUIMgr);
private:
	// �ֻ��� UI�� �� ��Ŀ�� ���� UI
	CUI* m_FocuedUI;

public:
	void tick();

private:
	CUI* GetPriorityCheck(CUI* _ParentUI);
};

