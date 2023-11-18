#include "pch.h"
#include "CCombo.h"

#include "CLogMgr.h"
#include "CAssetMgr.h"
#include "CTexture.h"
#include "CFever.h"

int AtlasWidth[10]	= { 62, 39,	61,	 60,  75,  61,  62,  62,  62,  61 };
int AtlasX[10]		= { 0,  62, 101, 162, 222, 297, 358, 420, 482, 544 };

CCombo::CCombo()
	:m_CurCombo(0)
	,m_BestCombo(0)
	,m_FeverPower()
	,m_ComboAtlas(nullptr)
	, m_ComboText(nullptr)
	, m_ComboUpOffset(0)
{ 
	m_ComboAtlas = FINDTEX(L"combo_num_atlas");
	m_ComboText = FINDTEX(L"combo_txt");
	CObj::SetPos(Vec2(307, 135));
}

CCombo::~CCombo()
{
}

void CCombo::tick(float _DT)
{

}

void CCombo::render(HDC _dc)
{
	// �ϴ� �ڸ� ���� �и��ؾ� �Ѵ�.
	// �ڸ� ���� �и��ϰ� ���� �ؽ��ĸ� ������־�� �Ѵ�.
	// ����, �ڸ� ���� ������ ���� �ʱ� ������ int�� ��� ���͸� ����ؼ� ���� ǥ���غ���...

	if (m_CurCombo == 0)
	{
		return;
	}

	static vector<int> m_NumOfDigits;
	m_NumOfDigits.clear();
	
	int CurComboBuf = m_CurCombo;
	int TotalWidth = 0;

	while (CurComboBuf)
	{
		m_NumOfDigits.push_back(CurComboBuf % 10); // ���� �ڸ� �� ���� ������� ����.
		TotalWidth += AtlasWidth[CurComboBuf % 10];
		CurComboBuf /= 10;
	}

	// �� -> �� ������ �ٲپ� �ֱ�.
	std::reverse(m_NumOfDigits.begin(), m_NumOfDigits.end());

	// ��� �߾� ��ġ�� �׻� �˰� �־�� �Ѵ�.
	// ��� �߾� ��ġ�κ��� �� ���� / 2��ŭ ���� ù ���ڸ� ������ �� ��ġ�� ���´�.
	// ���� ���ĺ��� �ϸ� �޺� ������ ������.
	// 

	// m_blend option
	BLENDFUNCTION m_blend;
	m_blend.BlendOp = AC_SRC_OVER;
	m_blend.BlendFlags = 0;
	m_blend.AlphaFormat = AC_SRC_ALPHA; // 0
	m_blend.SourceConstantAlpha = 255;

	Vec2 renderpos = GetPos();

	// combo text render - combo text �̹����� combo up offset�� ������ ���� �ʱ� ������, ���� ���� �����ϱ� ������ �ؽ�Ʈ �̹����� ���� ������ ��.
	AlphaBlend(_dc
		, renderpos.x - 54, renderpos.y - 40
		, 108, 30
		, m_ComboText->GetDC()
		, 0, 0
		, 108, 30
		, m_blend);

	// �ؽ�Ʈ �̹��� ��� �� ���� ���� ������ ���� ����ϰ� ����.
	m_blend.SourceConstantAlpha = 255 - (m_ComboUpOffset * 5);

	renderpos.x -= int(TotalWidth) / 2.f;


	for (int i = 0; i < m_NumOfDigits.size(); ++i)
	{
		int curDigit = m_NumOfDigits[i];

		AlphaBlend(_dc
			, renderpos.x, renderpos.y + (m_ComboUpOffset * 1.4)
			, AtlasWidth[curDigit], 118 + (m_ComboUpOffset * 1.4)
			, m_ComboAtlas->GetDC()
			, AtlasX[curDigit], 0
			, AtlasWidth[curDigit], 118 
			, m_blend);

		renderpos.x += AtlasWidth[curDigit];

		if (m_ComboUpOffset)
			m_ComboUpOffset -= 3;
	}


}

void CCombo::ComboUp(JUDGE_VECTOR_IDX _judge)
{
	if (JUDGE_VECTOR_IDX::BREAK == _judge)
	{
		ComboBreak();
		return;
	}
	// ���� Fever ������ ���� �޺� �� ������ ǥ���ؿ�.
	if (m_FeverPower != nullptr)
	{
		m_CurCombo += m_FeverPower->GetFeverPower();
		m_ComboUpOffset = 51;
	}
	else
		LOG(LOG_LEVEL::ERR, L"Combo ���� Fever �����Ͱ� nullptr�Դϴ�.");
}

void CCombo::ComboBreak()
{
	if (m_BestCombo < m_CurCombo)
		m_BestCombo = m_CurCombo;

	m_CurCombo = 0;
}
