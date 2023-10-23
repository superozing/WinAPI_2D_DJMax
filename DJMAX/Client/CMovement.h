#pragma once
#include "CComponent.h"

/* 무브먼트 컴포넌트
* 물리에 의한 움직임, 힘 처리에 특화
* 
*/
class CMovement :
    public CComponent
{
private:
    // 누적된 힘
    Vec2    m_Force;

    // 현재 가속도
    Vec2    m_Accel;

    // 속도
    Vec2    m_Velocity;

    // 질량
    float   m_Mass;

    // 보장된 초기 속력(너무 낮은 속도에서 부터 움직이지 않도록 해줌.)
    float   m_InitSpeed;

    // 최대 속력
    float   m_MaxSpeed;

    // 마찰 크기
    float   m_FrictionScale;

    // 중력 기능 On / Off
    bool    m_UseGravity;

    // 적용되고 있는 중력 방향 및 배율
    Vec2    m_GravityForce;

    // 땅위인지 아닌지 (땅 쪽 충돌 처리에서 사용)
    bool    m_Ground;


public:
    void AddForce(Vec2 _vForce)
    {
        m_Force += _vForce;
    }

    Vec2 GetForce()
    {
        return m_Force;
    }

    void SetVelocity(Vec2 _vVelocity)
    {
        m_Velocity = _vVelocity;
    }

    void AddVelocity(Vec2 _vAdd)
    {
        m_Velocity += _vAdd;
    }

    Vec2 GetVelocity()
    {
        return m_Velocity;
    }

    void SetMass(float _Mass)
    {
        m_Mass = _Mass;
    }

    float GetMass()
    {
        return m_Mass;
    }

    void SetInitSpeed(float _Speed)
    {
        m_InitSpeed = _Speed;
    }

    void SetMaxSpeed(float _Speed)
    {
        m_MaxSpeed = _Speed;
    }

    float GetInitSpeed()
    {
        return m_InitSpeed;
    }

    float GetMaxSpeed()
    {
        return m_MaxSpeed;
    }

    void SetFrictionScale(float _F)
    {
        m_FrictionScale = _F;
    }

    float GetFrictionScale()
    {
        return m_FrictionScale;
    }

    void UseGravity(bool _Use)
    {
        m_UseGravity = _Use;
    }

    bool IsUseGravity()
    {
        return m_UseGravity;
    }

    void SetGravity(Vec2 _vGravity)
    {
        m_GravityForce = _vGravity;
    }

    Vec2 GetGravityDir()
    {
        return Vec2(m_GravityForce).Normalize();
    }

    bool IsGround()
    {
        return m_Ground;
    }

    void SetGround(bool _Ground)
    {
        if (_Ground)
        {
            m_Velocity.y = 0.f;
        }

        m_Ground = _Ground;
    }

public:
    virtual void finaltick(float _DT) override;

public:
    //CLONE(CMovement);

    CMovement(CObj* _Owner);
    ~CMovement();
};