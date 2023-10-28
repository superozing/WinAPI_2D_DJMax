#pragma once
#include "CState.h"

class CMouseOn :
    public CState
{
private:
    // 간편하게 참조하기 위해서 포인터를 받아놓는 것도 좋은 방법이다.
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
