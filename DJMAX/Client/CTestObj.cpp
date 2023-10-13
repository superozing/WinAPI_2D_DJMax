#include "pch.h"
#include "CTestObj.h"

void CTestObj::tick(float _DT)
{
	CObj::tick(_DT);

}

void CTestObj::render(HDC _dc)
{
	Super::render(_dc);
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();

	Rectangle(_dc
		, int(vPos.x - vScale.x / 2)
		, int(vPos.y - vScale.y / 2)
		, int(vPos.x + vScale.x / 2)
		, int(vPos.y + vScale.y / 2));
}

CTestObj::CTestObj()
{
}

CTestObj::~CTestObj()
{
}
