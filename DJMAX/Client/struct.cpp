#include "pch.h"
#include "struct.h"

#include "CEngine.h"

FSelectPen::FSelectPen(HDC _dc, PEN_TYPE _Type)
	: hPrevPen(nullptr)
	, hCurDC(_dc)
{
	hPrevPen = (HPEN)SelectObject(hCurDC, CEngine::GetInst()->GetPen(_Type));
}

FSelectPen::~FSelectPen()
{
	SelectObject(hCurDC, hPrevPen);
}


FSelectBrush::FSelectBrush(HDC _dc, HBRUSH _brush)
	: hCurDC(_dc)
	, hPrevBrush(nullptr)
{
	hPrevBrush = (HBRUSH)SelectObject(hCurDC, _brush);
}

FSelectBrush::~FSelectBrush()
{
	SelectObject(hCurDC, hPrevBrush);
}
