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
{ 
	m_ComboAtlas = FINDTEX(L"combo_num_atlas");
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
	// 정확히 중앙 지점이 가운데에 오도록 해야 하는데...
	// 자릿 수가 1개 일 때에는 큰 문제 없어 보이는데
	// 자릿 수가 2개 이상일 경우를 생각해보아야 한다.
	// 음.. 일단 자릿 수가 1개일 경우에만 무언가를 해보자

	// 일단 자릿 수를 분리해야 한다.
	// 자릿 수를 분리하고 나서 텍스쳐를 출력해주어야 한다.
	// 만약 자릿 수가 12345라면 어떻게 분해할까?
	// 또한, 자릿 수가 정해져 있지 않기 때문에 int를 담는 벡터를 사용해서 값을 표시해보자...

	if (m_CurCombo == 0)
	{
		return;
	}

	static vector<int> numOfDigits;
	numOfDigits.clear();
	
	int CurComboBuf = m_CurCombo;
	int TotalWidth = 0;

	while (CurComboBuf)
	{
		numOfDigits.push_back(CurComboBuf % 10); // 낮은 자릿 수 부터 순서대로 들어가요.
		TotalWidth += AtlasWidth[CurComboBuf % 10];
		CurComboBuf /= 10;
	}

	// 높 -> 낮 순서로 바꾸어 주기.
	std::reverse(numOfDigits.begin(), numOfDigits.end());

	// 기어 중앙 위치를 항상 알고 있어야 한다.
	// 기어 중앙 위치로부터 총 넓이 / 2만큼 빼면 첫 숫자를 렌더링 할 위치가 나온다.
	// 쭉쭉 알파블렌드 하면 콤보 렌더는 끝난다.
	// 

	BLENDFUNCTION blend;
	blend.BlendOp = AC_SRC_OVER;
	blend.BlendFlags = 0;
	blend.AlphaFormat = AC_SRC_ALPHA; // 0
	blend.SourceConstantAlpha = 255;

	Vec2 renderpos = GetPos();

	renderpos.x -= int(TotalWidth) / 2.f;

	for (int i = 0; i < numOfDigits.size(); ++i)
	{
		int curDigit = numOfDigits[i];

		AlphaBlend(_dc
			, renderpos.x, renderpos.y
			, AtlasWidth[curDigit], 118
			, m_ComboAtlas->GetDC()
			, AtlasX[curDigit], 0
			, AtlasWidth[curDigit], 118
			, blend);

		renderpos.x += AtlasWidth[curDigit];
	}


}

void CCombo::ComboUp(JUDGE_VECTOR_IDX _judge)
{
	if (JUDGE_VECTOR_IDX::BREAK == _judge)
	{
		ComboBreak();
		return;
	}
	// 현재 Fever 배율에 따른 콤보 수 증가를 표현해요.
	if (m_FeverPower != nullptr)
		m_CurCombo += m_FeverPower->GetFeverPower();
	else
		LOG(LOG_LEVEL::ERR, L"Combo 쪽의 Fever 포인터가 nullptr입니다.");
}

void CCombo::ComboBreak()
{
	if (m_BestCombo < m_CurCombo)
		m_BestCombo = m_CurCombo;

	m_CurCombo = 0;
}
