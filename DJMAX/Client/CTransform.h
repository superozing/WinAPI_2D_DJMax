#pragma once
#include "CComponent.h"
/// <summary>
/// 
/// </summary>
class CTransform :
    public CComponent
{
private:
    Vec2 m_Point;
    float m_Speed;

public:
    virtual void finaltick(float _DT) override;
    /// <summary>
    /// 원하는 위치로 옮기는 함수
    /// </summary>
    /// <param name="_Point">목적지</param>
    /// <param name="_duration">걸리는 시간, 0 일 경우 바로 이동</param>
    void MoveTo(Vec2 _Point, float _duration = 0);
    /// <summary>
    /// 
    /// </summary>
    /// <param name="_point"></param>
    void SetTargetPoint(Vec2 _point) { m_Point = _point; }


public:
    CLONE(CTransform);
    CTransform(CObj* _Owner);
    ~CTransform();
};

