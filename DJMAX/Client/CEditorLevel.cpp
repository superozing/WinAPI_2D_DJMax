#include "pch.h"
#include "CEditorLevel.h"

#include "CTestObj.h"

void CEditorLevel::init()
{
}

void CEditorLevel::enter()
{
	CTestObj* ct = new CTestObj();
	ct->SetPos(Vec2{ 0.f,0.f });
	ct->SetScale(Vec2{ 200,200 });
	AddObject(LAYER::DEFAULT, ct);
	
}

void CEditorLevel::exit()
{
}

void CEditorLevel::tick()
{
}
