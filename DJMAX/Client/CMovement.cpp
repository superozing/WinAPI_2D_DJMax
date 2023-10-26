#include "pch.h"
#include "CMovement.h"

#include "CObj.h"

CMovement::CMovement(CObj* _Owner)
	:CComponent(_Owner)
	, m_Mass(1.f)
	, m_InitSpeed(0.f)
	, m_MaxSpeed(0.f)
	, m_FrictionScale(0.f)
	, m_UseGravity(false)
	, m_Ground(false)
{
}

CMovement::~CMovement()
{
}

void CMovement::finaltick(float _DT)
{
	// 힘 = 질량 * 가속도, 가속도 = 힘 / 질량 
	// 방향 벡터
	m_Accel = m_Force / m_Mass;

	// 중력 적용
	if (m_UseGravity && !m_Ground)
	{
		m_Accel += m_GravityForce;
	}

	// 정지 상태(와 가까운 상태)면서 가속도가 없을 경우
	if (m_Velocity.Length() < 0.1f && (!m_Accel.IsZero()))
	{
		// 초기 속도를 맟춰줌
		Vec2 vAccelDir = m_Accel;
		vAccelDir.Normalize(); // 방향 벡터
		m_Velocity = vAccelDir * m_InitSpeed;
	}
	else
	{
		m_Velocity += m_Accel * _DT;
	}

	// 최대 속도 제한
	if (abs(m_Velocity.x) > m_MaxSpeed)
	{
		m_Velocity.x = (m_Velocity.x / abs(m_Velocity.x)) * m_MaxSpeed;
	}

	// 물체에 적용되고 있는 힘이 없으면 마찰력을 적용시킴
	if (m_Force.IsZero() && m_Velocity.x != 0.f && m_Ground)
	{
		float fFriction = -m_Velocity.x;
		fFriction /= abs(fFriction);

		fFriction *= m_FrictionScale;

		float fFrictionAccel = (fFriction / m_Mass) * _DT;
		if (abs(m_Velocity.x) < abs(fFrictionAccel))
		{
			m_Velocity = Vec2(0.f, m_Velocity.y);
		}
		else
		{
			m_Velocity.x += fFrictionAccel;
		}
	}
	
	// 힘 설정
	Vec2 vObjPos = GetOwner()->GetPos();
	vObjPos += m_Velocity * _DT;
	GetOwner()->SetPos(vObjPos);

	// 힘 리셋
	m_Force = Vec2(0.f, 0.f);
}
