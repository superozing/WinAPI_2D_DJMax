#include "pch.h"
#include "CGear.h"

#include "CAssetMgr.h"
#include "CTimeMgr.h"
#include "CTexture.h"
#include "CNote.h"
#include "CSound.h"

CGear::CGear()
	:m_blendFunc{}
	,m_vecNotes()
	,m_GearTexture(nullptr)
{
	// blend function setting
	m_blendFunc.BlendOp = AC_SRC_OVER;
	m_blendFunc.BlendFlags = 0;

	m_blendFunc.SourceConstantAlpha = 255; // 0 ~ 255
	m_blendFunc.AlphaFormat = AC_SRC_ALPHA; // 0
	
	// texture
	m_GearTexture = FINDTEX(L"gear_default");
	SetPos(Vec2(50,-13));

	m_GearJudgeLine = FINDTEX(L"ÆÇÁ¤¼±");

}

CGear::~CGear()
{
}

void CGear::tick(float _DT)
{
	Super::tick(_DT);
}

void CGear::render(HDC _dc)
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();
	if (nullptr != m_GearTexture)
	{
		Vec2 vImgScale = Vec2((float)m_GearTexture->GetWidth(), (float)m_GearTexture->GetHeight());
		AlphaBlend(_dc
			, int(vPos.x), int(vPos.y)
			, int(vImgScale.x * 0.8333f), int(vImgScale.y * 0.8333f)
			, m_GearTexture->GetDC()
			, 0, 0
			, int(vImgScale.x), int(vImgScale.y)
			, m_blendFunc);
	}
	static float m_AccMusicTime;

	m_AccMusicTime += DT;
	float curMusicTime = 141 * m_AccMusicTime;

	for (auto& iter : m_vecNotes)
	{
		iter.render(_dc, curMusicTime, 4.f);
	}

	if (nullptr != m_GearTexture)
	{
		Vec2 vImgScale = Vec2((float)m_GearJudgeLine->GetWidth(), (float)m_GearJudgeLine->GetHeight());
		AlphaBlend(_dc
			, int(vPos.x), int(vPos.y)
			, 418, int(vImgScale.y * 0.8333f)
			, m_GearTexture->GetDC()
			, 0, 0
			, int(vImgScale.x), int(vImgScale.y)
			, m_blendFunc);
	}


	Super::render(_dc);
}

void CGear::AddNote(NOTE_TYPE _type, float _tapTime, float _pressTime, GEARLINE_TYPE _line)
{
	m_vecNotes.push_back(CNote(_type, _tapTime, _pressTime, _line, this));
}

void CGear::LoadNoteData()
{
}

void CGear::SaveNoteData()
{
}
