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

	if (m_CurCombo == 0 || !m_ComboRender)
	{
		return;
	}

	static vector<int> numOfDigits;
	numOfDigits.clear();
	
	int CurComboBuf = m_CurCombo;
	int TotalWidth = 0;

	while (CurComboBuf)
	{
		numOfDigits.push_back(CurComboBuf % 10); // ���� �ڸ� �� ���� ������� ����.
		TotalWidth += AtlasWidth[CurComboBuf % 10];
		CurComboBuf /= 10;
	}

	// �� -> �� ������ �ٲپ� �ֱ�.
	std::reverse(numOfDigits.begin(), numOfDigits.end());

	// ��� �߾� ��ġ�� �׻� �˰� �־�� �Ѵ�.
	// ��� �߾� ��ġ�κ��� �� ���� / 2��ŭ ���� ù ���ڸ� ������ �� ��ġ�� ���´�.
	// ���� ���ĺ��� �ϸ� �޺� ������ ������.
	// 

	// blend option
	BLENDFUNCTION blend;
	blend.BlendOp = AC_SRC_OVER;
	blend.BlendFlags = 0;
	blend.AlphaFormat = AC_SRC_ALPHA; // 0
	blend.SourceConstantAlpha = 255;

	Vec2 renderpos = GetPos();

	// combo text render - combo text �̹����� combo up offset�� ������ ���� �ʱ� ������, ���� ���� �����ϱ� ������ �ؽ�Ʈ �̹����� ���� ������ ��.
	AlphaBlend(_dc
		, renderpos.x - 54, renderpos.y - 40
		, 108, 30
		, m_ComboText->GetDC()
		, 0, 0
		, 108, 30
		, blend);

	// �ؽ�Ʈ �̹��� ��� �� ���� ���� ������ ���� ����ϰ� ����.
	blend.SourceConstantAlpha = 255 - (m_ComboUpOffset * 5);

	renderpos.x -= int(TotalWidth) / 2.f;


	for (int i = 0; i < numOfDigits.size(); ++i)
	{
		int curDigit = numOfDigits[i];

		AlphaBlend(_dc
			, renderpos.x, renderpos.y + (m_ComboUpOffset * 1.4)
			, AtlasWidth[curDigit], 118 + (m_ComboUpOffset * 1.4)
			, m_ComboAtlas->GetDC()
			, AtlasX[curDigit], 0
			, AtlasWidth[curDigit], 118 
			, blend);

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
		StartComboRender();
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
