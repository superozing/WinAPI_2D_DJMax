#include "pch.h"
#include "CNumTexture.h"

void CNumTexture::tick(float _DT)
{
}

void CNumTexture::render(HDC _dc)
{
}

CNumTexture::CNumTexture()
	: m_FontSize(20)
	, m_RealNumber(.0f)
{
}

CNumTexture::CNumTexture(const CNumTexture& _Origin)
	: m_FontSize(_Origin.m_FontSize)
	, m_RealNumber(_Origin.m_RealNumber)
{
}

CNumTexture::~CNumTexture()
{
}
