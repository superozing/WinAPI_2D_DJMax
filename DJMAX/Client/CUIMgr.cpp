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

/* 키 입력 판정의 기본 전제
* 키 입력은 윈도우 표준을 따름
* 마우스의 왼 쪽 버튼이 위로 올라온 오브젝트를 "클릭" 한 오브젝트라고 봄.
* 마우스의 왼 쪽 버튼이 언제 어디에서 아래로 내려가도 상관 없음.
* 무조건 왼 쪽 버튼이 위로 올라온 경우에 클릭 된 UI 라고 판단
*/

void CUIMgr::tick()
{
    // 실제 마우스의 키입력
    Vec2 vMousePos = CKeyMgr::GetInst()->GetMousePos();
    bool bLBtnTap = KEY_TAP(KEY::LBTN);
    bool bLbtnReleased = KEY_RELEASED(KEY::LBTN);

    // 검사
    CLevel* pLevel = CLevelMgr::GetInst()->GetCurLevel();
    if (nullptr == pLevel)
    {
        LOG(LOG_LEVEL::LOG, L"CUIMgr에서 레벨 매니저가 nullptr임. 첫 프레임에 떠야 함");
        return;
    }

    // UI레이어 가져오기
    CLayer* pUILayer = pLevel->GetLayer(LAYER::UI);
    vector<CObj*>& vecUI = pUILayer->m_vecObjects;
    auto riter = vecUI.rbegin();

    // 순회
    for (riter; riter != vecUI.rend(); ++riter)
    {
        CUI* pUI = dynamic_cast<CUI*>(*riter); // 불안하면 안전한 길을 골라요.

        // UI레이어 내의 UI가 아닌 데이터 체크
        if (nullptr == pUI)
        {
            LOG(LOG_LEVEL::ERR, L"UI레이어에 UI가 아닌 다른 오브젝트가 들어 있음.");
            continue;
        }

        // 현재 마우스가 UI위에 올라와 있는가?
        if (pUI->m_bMouseOn)
        {
			// 올라와 있을 경우, 현재 포커싱 되는 최상위 UI는 이 UI이다.
			m_FocuedUI = pUI;

			// 해당 최상위 UI 내부에서 어떤 UI가 가장 우선 순위가 높게 클릭되는지 체크.
			pUI = GetPriorityCheck(pUI);

			// 현재 마우스가 올라와 있는 상태이지만, 이전 마우스가 UI위에 올라와 있지 않았다면
			if (pUI->m_bMouseOn_Prev != pUI->m_bMouseOn)
			{
				// 올라옴(OnHovered)
				pUI->OnHovered(vMousePos);
			}
			// 이전 마우스 위치에 이어 현재 마우스가 계속 올라와있다면
			else
			{
				// 지속적으로 올라와있음(MouseOn)
				pUI->MouseOn(vMousePos);
			}

			// 현재 마우스가 올라와 있는 상태에서 UI 위에서 왼쪽 버튼을 뗀 경우
			if (bLbtnReleased)
			{
				// 클릭 처리(LBtnUp)
				pUI->LBtnUp(vMousePos);

				// 해당 UI 위에서 마우스 왼 쪽 버튼을 누르고 나가지 않았다면?
				if (pUI->m_bMouseLBtnDown)
				{
					pUI->LBtnClicked(vMousePos);
				}
			}

			// 현재 마우스가 Tap 상태에서 
			if (bLBtnTap)
			{
				// UI 위에서 왼 쪽 버튼을 누른 경우
				pUI->LBtnDown(vMousePos);
				pUI->m_bMouseLBtnDown = true;

				// reverse iterator 로 vector 내에서 erase 하기
				std::advance(riter, 1);
				vecUI.erase(riter.base());

				vecUI.push_back(m_FocuedUI);
			}

			// m_bMouseLBtnDown을 원상복구
			if (bLbtnReleased)
			{
				pUI->m_bMouseLBtnDown = false;
			}

			break;
		}
		else
		{
			// 마우스가 이전 프레임에 오브젝트에 올라와있었지만, 지금은 올라와 있지 않을 때.
			if (pUI->m_bMouseOn_Prev != pUI->m_bMouseOn)
			{
				// 올라옴 해제(OnUnHovered)
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
	// 현재 클릭 입력을 사용할 UI 초기화
	CUI* pPriorityUI = nullptr;

	// 계속 재할당 하지 않고 재활용 하기
	static list<CUI*> queue;
	queue.clear();

	queue.push_back(_ParentUI);

	// 레벨 단위 순차 탐색
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
			// 포커싱 되어있는 UI를 계속 최신으로 변경해가면서, 마지막에 도달했을 때 최종 포커싱 UI를 찾을 수 있다
			pPriorityUI = pUI;
		}
	}

	return pPriorityUI;
}