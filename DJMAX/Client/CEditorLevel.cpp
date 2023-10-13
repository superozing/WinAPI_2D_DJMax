#include "pch.h"
#include "CEditorLevel.h"

#include "CTestObj.h"

void CEditorLevel::init()
{
}

void CEditorLevel::enter()
{
	CTestObj* ct = new CTestObj();
	ct->SetPos(Vec2{ 1000,1000 });
	ct->SetScale(Vec2{ 1000,1000 });
	AddObject(LAYER::DEFAULT, ct);
	
}

void CEditorLevel::exit()
{
}

void CEditorLevel::tick()
{
}
