#include "pch.h"
#include "CMouseOn.h"

CMouseOn::CMouseOn()
{
}
CMouseOn::~CMouseOn()
{
}
void CMouseOn::finaltick(float _DT)
{
	//float* pDetectRange = (float*)GetOwnerSM()->GetDataFromBlackboard(L"Detect Range");

	//if()
	GetOwnerSM()->ChangeState((UINT)ESTARTLEVEL_CHOICE_STATE::MOUSE_ON); // 부모 쪽(statemachine)에서 다른 State로 변경할 수 있음.
}

void CMouseOn::Enter()
{
	//CAnimator* pAnimator = GetOwnerSM()->GetOwner()->GetComponent<CAnimator>();
	//pAnimator->Play(L"")

	// 레벨에 있는 플레이어를 알아낸다.
	//m_pTarget = dynamic_cast<CPlayer*>(CLevelMgr::GetInst()->GetCurLevel()->FindObjectByName(L"Player"));
}

void CMouseOn::Exit()
{
}
