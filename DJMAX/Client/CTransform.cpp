#include "pch.h"
#include "CTransform.h"

#include "CObj.h"

CTransform::CTransform(CObj* _Owner):
	CComponent(_Owner)
{
	
}

CTransform::~CTransform()
{
}

void CTransform::finaltick(float _DT)
{
	Vec2 vPos = GetOwner()->GetPos();
	Vec2 vDir = m_Point - vPos;
	if (vDir.Length() <= 1.f) {
		GetOwner()->SetPos(m_Point);
		return;
	}

	vDir.Normalize();

	vPos += vDir * m_Speed * _DT;
	GetOwner()->SetPos(vPos);
}

void CTransform::MoveTo(Vec2 _Point, float _duration)
{
	if (_duration == 0) {
		GetOwner()->SetPos(_Point);
		m_Point = _Point;
		return;
	}
	m_Point = _Point;
	m_Speed = (m_Point - GetOwner()->GetPos()).Length()/_duration;
}
