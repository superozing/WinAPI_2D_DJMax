#include "pch.h"
#include "CUIMgr.h"

#include "CKeyMgr.h"

#include "CLevelMgr.h"
#include "CLevel.h"
#include "CLayer.h"
#include "CUI.h"

#include "CLogMgr.h"

CUIMgr::CUIMgr()
    :m_FocuedUI(nullptr)
{

}

CUIMgr::~CUIMgr()
{

}

/* Ű �Է� ������ �⺻ ����
* Ű �Է��� ������ ǥ���� ����
* ���콺�� �� �� ��ư�� ���� �ö�� ������Ʈ�� "Ŭ��" �� ������Ʈ��� ��.
* ���콺�� �� �� ��ư�� ���� ��𿡼� �Ʒ��� �������� ��� ����.
* ������ �� �� ��ư�� ���� �ö�� ��쿡 Ŭ�� �� UI ��� �Ǵ�
*/

void CUIMgr::tick()
{
    // ���� ���콺�� Ű�Է�
    Vec2 vMousePos = CKeyMgr::GetInst()->GetMousePos();
    bool bLBtnTap = KEY_TAP(KEY::LBTN);
    bool bLbtnReleased = KEY_RELEASED(KEY::LBTN);

    // �˻�
    CLevel* pLevel = CLevelMgr::GetInst()->GetCurLevel();
    if (nullptr == pLevel)
    {
        LOG(LOG_LEVEL::ERR, L"CUIMgr���� ���� �Ŵ����� nullptr��. �Ƹ��� ù �����ӿ� �� �α��Դϴ�.");
        return;
    }

    // UI���̾� ��������
    CLayer* pUILayer = pLevel->GetLayer(UI);
    vector<CObj*>& vecUI = pUILayer->m_vecObjects;
    auto riter = vecUI.rbegin();

    // ��ȸ
    for (riter; riter != vecUI.rend(); ++riter)
    {
        CUI* pUI = dynamic_cast<CUI*>(*riter); // �Ҿ��ϸ� ������ ���� ����.

        // UI���̾� ���� UI�� �ƴ� ������ üũ
        if (nullptr == pUI)
        {
            LOG(LOG_LEVEL::ERR, L"UI���̾ UI�� �ƴ� �ٸ� ������Ʈ�� ��� ����.");
            continue;
        }

        // ���� ���콺�� UI���� �ö�� �ִ°�?
        if (pUI->m_bMouseOn)
        {
			// �ö�� ���� ���, ���� ��Ŀ�� �Ǵ� �ֻ��� UI�� �� UI�̴�.
			m_FocuedUI = pUI;

			// �ش� �ֻ��� UI ���ο��� � UI�� ���� �켱 ������ ���� Ŭ���Ǵ��� üũ.
			pUI = GetPriorityCheck(pUI);

			// ���� ���콺�� �ö�� �ִ� ����������, ���� ���콺�� UI���� �ö�� ���� �ʾҴٸ�
			if (pUI->m_bMouseOn_Prev != pUI->m_bMouseOn)
			{
				// �ö��(OnHovered)
				pUI->OnHovered(vMousePos);
			}
			// ���� ���콺 ��ġ�� �̾� ���� ���콺�� ��� �ö���ִٸ�
			else
			{
				// ���������� �ö������(MouseOn)
				pUI->MouseOn(vMousePos);
			}

			// ���� ���콺�� �ö�� �ִ� ���¿��� UI ������ ���� ��ư�� �� ���
			if (bLbtnReleased)
			{
				// Ŭ�� ó��(LBtnUp)
				pUI->LBtnUp(vMousePos);

				// �ش� UI ������ ���콺 �� �� ��ư�� ������ ������ �ʾҴٸ�?
				if (pUI->m_bMouseLBtnDown)
				{
					pUI->LBtnClicked(vMousePos);
				}
			}

			// ���� ���콺�� Tap ���¿��� 
			if (bLBtnTap)
			{
				// UI ������ �� �� ��ư�� ���� ���
				pUI->LBtnDown(vMousePos);
				pUI->m_bMouseLBtnDown = true;

				// reverse iterator �� vector ������ erase �ϱ�
				std::advance(riter, 1);
				vecUI.erase(riter.base());

				vecUI.push_back(m_FocuedUI);
			}

			// m_bMouseLBtnDown�� ���󺹱�
			if (bLbtnReleased)
			{
				pUI->m_bMouseLBtnDown = false;
			}

			break;
		}
		else
		{
			// ���콺�� ���� �����ӿ� ������Ʈ�� �ö���־�����, ������ �ö�� ���� ���� ��.
			if (pUI->m_bMouseOn_Prev != pUI->m_bMouseOn)
			{
				// �ö�� ����(OnUnHovered)
				pUI->OnUnHovered(vMousePos);
			}

			if (bLbtnReleased)
			{
				pUI->m_bMouseLBtnDown = false;
			}
		}
	}
}

CUI* CUIMgr::GetPriorityCheck(CUI* _ParentUI)
{
	// ���� Ŭ�� �Է��� ����� UI �ʱ�ȭ
	CUI* pPriorityUI = nullptr;

	// ��� ���Ҵ� ���� �ʰ� ��Ȱ�� �ϱ�
	static list<CUI*> queue;
	queue.clear();

	queue.push_back(_ParentUI);

	// ���� ���� ���� Ž��
	while (!queue.empty())
	{
		CUI* pUI = queue.front();
		queue.pop_front();

		for (size_t i = 0; i < pUI->m_vecChildUI.size(); ++i)
		{
			queue.push_back(pUI->m_vecChildUI[i]);
		}

		if (pUI->m_bMouseOn)
		{
			// ��Ŀ�� �Ǿ��ִ� UI�� ��� �ֽ����� �����ذ��鼭, �������� �������� �� ���� ��Ŀ�� UI�� ã�� �� �ִ�
			pPriorityUI = pUI;
		}
	}

	return pPriorityUI;
}