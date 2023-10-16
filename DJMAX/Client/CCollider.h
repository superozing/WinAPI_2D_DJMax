#pragma once
#include "CEntity.h"
#include "CComponent.h"

class CObj;

class CCollider :
    public CComponent
{
private:
    Vec2    m_vOffsetPos;  // Owner 로부터 떨어진 거리
    Vec2    m_vScale;      // Owner 로부터 추가 배율
    Vec2    m_vFinalPos;   // 충돌체의 최종 위치

    int     m_iCollisionCount;

public:
    virtual void finaltick(float _DT) override;
    virtual void render(HDC _dc) override;

public:
    void SetOffsetPos(Vec2 _vOffsetPos) { m_vOffsetPos = _vOffsetPos; }
    void SetScale(Vec2 _vScale) { m_vScale = _vScale; }
    Vec2 GetPos() { return m_vFinalPos; }
    Vec2 GetOffsetPos() { return m_vOffsetPos; }
    Vec2 GetScale() { return m_vScale; }


public:
    void BeginOverlap(CCollider* _OtherCol);
    void Overlap(CCollider* _OtherCol);
    void EndOverlap(CCollider* _OtherCol);


public:
    CCollider(CObj* _Owner);
    ~CCollider();
};

