#pragma once
#include "CEntity.h"
#include "CStateMachine.h"

#include "CObj.h"
#include "CAnimator.h"

#include "CLevelMgr.h"
#include "CLevel.h"


class CState :
    public CEntity
{
private:
    CStateMachine*  m_pSM;     // �ڽ��� ������ StateMachine
    UINT            m_StateID; // ID -> enum �Ǵ� enum class�� ������ ������ ġȯ�ؼ� ���


public:
    CStateMachine* GetOwnerSM() { return m_pSM; }
    UINT GetStateID() { return m_StateID; }

public:
    virtual void finaltick(float _DT) = 0;
    virtual void Enter() = 0;
    virtual void Exit() = 0;

public:
    virtual CState* Clone() = 0;

public:
    CState();
    ~CState();

    friend class CStateMachine;
};

/* ���� State �߰� ���
class CNormalMonIdle :
    public CState
{
private:
    // �ڽ��� ����ų �÷��̾�. �����ϰ� �����ϱ� ���ؼ� �÷��̾� �����͸� �޾Ƴ��� �͵� ���� ����̴�.
    CPlayer*    m_pTarget; 

public:
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CNormalMonIdle);
    CNormalMonIdle();
    ~CNormalMonIdle();
};


* cpp
#include "pch.h"
#include "CNormalMonIdle.h"

CNormalMonIdle::CNormalMonIdle()
{
}
CNormalMonIdle::~CNormalMonIdle()
{
}
void CNormalMonIdle::finaltick(float _DT)
{
	// �÷��̾ ����Ű�� ���� ���� ���
	if (nullptr == m_pTarget)
		return;

	// �÷��̾ Ž������ ���� �ִ��� Ȯ��
	// 1. �����忡 ����Ǿ��ִ� Ž�������� �����´� (�̷� ������ �����忡 �����͸� �־����, ���� �� ������ �� �ִ�.)
	float* pDetectRange = (float*)GetOwnerSM()->GetDataFromBlackboard(L"Detect Range");
	float DetectRange = *pDetectRange;

	// 2. �÷��̾�� ���Ͱ��� �Ÿ��� üũ
	Vec2 vPlayerPos = m_pTarget->GetPos();
	CMonster* pMonster = dynamic_cast<CMonster*>(GetOwnerSM()->GetOwner()); // �θ� ��(statemachine)���� �÷��̾�*�� �����ؼ�, ��ġ ���� ��������.
	if (nullptr == pMonster)
		return;

	Vec2 vMonsterPos = pMonster->GetPos();

	float fDist = vPlayerPos.Distance(vMonsterPos);

	if (fDist < DetectRange)
	{
		GetOwnerSM()->ChangeState((UINT)ENORMAL_MON_STATE::NORMAL_MON_TRACE); // �θ� ��(statemachine)���� �ٸ� State�� ������ �� ����.
	}
}

void CNormalMonIdle::Enter()
{
	//CAnimator* pAnimator = GetOwnerSM()->GetOwner()->GetComponent<CAnimator>();
	//pAnimator->Play(L"")

	// ������ �ִ� �÷��̾ �˾Ƴ���.
	m_pTarget = dynamic_cast<CPlayer*>(CLevelMgr::GetInst()->GetCurLevel()->FindObjectByName(L"Player"));
}

void CNormalMonIdle::Exit()
{
}



* ���� �ּ����� ��Ÿ���� "�θ� ��": ��� ���谡 �ƴ� ���� ����.
*/