#include "pch.h"
#include "CNumTexture.h"
#include "CAssetMgr.h"
#include "CTexture.h"

CNumTexture::CNumTexture()
	: m_FontSize(1)
	, m_RealNumber(.0f)
	, m_isRealNumber(false)
	, m_NumAtlas(FINDTEX(L"num_atlas"))
	, m_blend{ AC_SRC_OVER, 0, AC_SRC_ALPHA, 255 }
{
	SetScale(Vec2(1000, 130));

	ResetVector();
}


CNumTexture::CNumTexture(float _FontSize)
	: m_FontSize(_FontSize)
	, m_RealNumber(.0f)
	, m_isRealNumber(false)
	, m_NumAtlas(FINDTEX(L"num_atlas"))
	, m_blend{ AC_SRC_OVER, 0, AC_SRC_ALPHA, 255 }
{
	SetScale(Vec2(1000, 130));
}

CNumTexture::CNumTexture(const CNumTexture& _Origin)
	: m_FontSize(_Origin.m_FontSize)
	, m_RealNumber(_Origin.m_RealNumber)
	, m_isRealNumber(_Origin.m_isRealNumber)
	, m_NumAtlas(FINDTEX(L"num_atlas"))
	, m_blend(_Origin.m_blend)
{
	SetScale(Vec2(1000, 130));
}

CNumTexture::~CNumTexture()
{
}

void CNumTexture::render(HDC _dc)
{
	Vec2 Pos	= GetPos();
	Vec2 Scale	= GetScale();

	Scale *= m_FontSize;

	for (int i = 0; i < m_NumOfDigits.size(); ++i)
	{
		AlphaBlend(_dc
			, Pos.x * (i * Scale.x), Pos.y
			, Scale.x, Scale.y
			, m_NumAtlas->GetDC()
			, 100 * i, 0
			, 100, 130
			, m_blend);
	}
}

void CNumTexture::ResetVector()
{
	m_NumOfDigits.clear();

	int iCurComboBuf = 0;

	// �Ǽ�, ������ ���� �ٸ� ���� �ϱ�
	if (m_isRealNumber) iCurComboBuf = m_RealNumber * 100;
	else 				iCurComboBuf = m_RealNumber;

	// �ڸ� �� �и�
	while (iCurComboBuf)
	{
		m_NumOfDigits.push_back(iCurComboBuf % 10); // ���� �ڸ� �� ���� ������� ����.
		iCurComboBuf /= 10;
	}

	// �� -> �� ������ �ٲپ� �ֱ�.
	std::reverse(m_NumOfDigits.begin(), m_NumOfDigits.end());
}
