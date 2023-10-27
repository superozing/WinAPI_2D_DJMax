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
    CStateMachine*  m_pSM;     // 자신이 소유한 StateMachine
    UINT            m_StateID; // ID -> enum 또는 enum class로 정수형 값으로 치환해서 사용


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

/* 예시 State 추가 방법
class CNormalMonIdle :
    public CState
{
private:
    // 자신이 가리킬 플레이어. 간편하게 참조하기 위해서 플레이어 포인터를 받아놓는 것도 좋은 방법이다.
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
	// 플레이어를 가리키고 있지 않을 경우
	if (nullptr == m_pTarget)
		return;

	// 플레이어가 탐지범위 내에 있는지 확인
	// 1. 블랙보드에 저장되어있는 탐지범위를 가져온다 (이런 식으로 블랙보드에 데이터를 넣어놓고, 원할 때 꺼내올 수 있다.)
	float* pDetectRange = (float*)GetOwnerSM()->GetDataFromBlackboard(L"Detect Range");
	float DetectRange = *pDetectRange;

	// 2. 플레이어와 몬스터간의 거리를 체크
	Vec2 vPlayerPos = m_pTarget->GetPos();
	CMonster* pMonster = dynamic_cast<CMonster*>(GetOwnerSM()->GetOwner()); // 부모 쪽(statemachine)에서 플레이어*를 참조해서, 위치 정보 가져오기.
	if (nullptr == pMonster)
		return;

	Vec2 vMonsterPos = pMonster->GetPos();

	float fDist = vPlayerPos.Distance(vMonsterPos);

	if (fDist < DetectRange)
	{
		GetOwnerSM()->ChangeState((UINT)ENORMAL_MON_STATE::NORMAL_MON_TRACE); // 부모 쪽(statemachine)에서 다른 State로 변경할 수 있음.
	}
}

void CNormalMonIdle::Enter()
{
	//CAnimator* pAnimator = GetOwnerSM()->GetOwner()->GetComponent<CAnimator>();
	//pAnimator->Play(L"")

	// 레벨에 있는 플레이어를 알아낸다.
	m_pTarget = dynamic_cast<CPlayer*>(CLevelMgr::GetInst()->GetCurLevel()->FindObjectByName(L"Player"));
}

void CNormalMonIdle::Exit()
{
}



* 위의 주석에서 나타내는 "부모 쪽": 상속 관계가 아닌 포함 관계.
*/