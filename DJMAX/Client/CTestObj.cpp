#include "pch.h"
#include "CTestObj.h"
#include "CCamera.h"

void CTestObj::tick(float _DT)
{
	CObj::tick(_DT);

}

void CTestObj::render(HDC _dc)
{
	Vec2 vPos = GetRenderPos();
	Vec2 vScale = GetScale();

	Rectangle(_dc
		, int(vPos.x - vScale.x / 2)
		, int(vPos.y - vScale.y / 2)
		, int(vPos.x + vScale.x / 2)
		, int(vPos.y + vScale.y / 2));
	Super::render(_dc);
}

CTestObj::CTestObj()
{
	m_Collider = AddComponent<CCollider>(L"TestCollider");
	m_Collider->SetScale(Vec2(900.f, 100.f));
	//m_Collider->
	//m_Collider->SetOffsetPos(Vec2(100.f, 100.f));
}

CTestObj::~CTestObj()
{
}
