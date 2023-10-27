#pragma once
#include "CObj.h"

class CTestObj
	: public CObj
{
	GENERATED_OBJECT(CObj);
private:
	CCollider* m_Collider;
public:
	virtual void tick(float _DT) override;
	virtual void render(HDC _dc) override;

public:
	CLONE(CTestObj);
	CTestObj();
	// 넌 기본 써라 ㅇㅇ;;;
	~CTestObj();
};

