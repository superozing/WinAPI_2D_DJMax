#pragma once
#include "CEntity.h"

class CObj;

class CComponent :
    public CEntity
{
private:
    CObj* m_pOwner; // 소유자

public:
    CObj* GetOwner() { return m_pOwner; }

public:
    virtual void tick(float _DT) {}
    virtual void finaltick(float _DT) = 0;
    virtual void render(HDC _dc) {}

public:
    virtual CComponent* Clone() = 0;    
    // Clone(복사 생성자)을 사용하지 않는 순수가상함수가 정의된 부모 쪽에서 순수 가상함수로 구현해야 하는 이유:
    // 만약 안한다면 Entity포인터로 반환될 뿐, 잘 작동하는데
    // 이 때 보통 오브젝트 객체를 생성하고 Clone으로 받을 때 만약 Component라면 한 번 더 다이나믹 캐스트를 사용해야 함

public:
    CComponent(CObj* _Owner);
    ~CComponent();

    friend class CObj;
};

