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
	GetOwnerSM()->ChangeState((UINT)ESTARTLEVEL_CHOICE_STATE::MOUSE_ON); // �θ� ��(statemachine)���� �ٸ� State�� ������ �� ����.
}

void CMouseOn::Enter()
{
	//CAnimator* pAnimator = GetOwnerSM()->GetOwner()->GetComponent<CAnimator>();
	//pAnimator->Play(L"")

	// ������ �ִ� �÷��̾ �˾Ƴ���.
	//m_pTarget = dynamic_cast<CPlayer*>(CLevelMgr::GetInst()->GetCurLevel()->FindObjectByName(L"Player"));
}

void CMouseOn::Exit()
{
}
