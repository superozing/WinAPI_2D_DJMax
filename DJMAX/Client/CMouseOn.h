#pragma once
#include "CState.h"

class CMouseOn :
    public CState
{
private:
    // �����ϰ� �����ϱ� ���ؼ� �����͸� �޾Ƴ��� �͵� ���� ����̴�.
    //CLevelChoice* m_SM;

public:
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CMouseOn);
    CMouseOn();
    ~CMouseOn();
};
