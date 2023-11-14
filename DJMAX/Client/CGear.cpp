#include "pch.h"
#include "CGear.h"

#include "CAssetMgr.h"
#include "CTimeMgr.h"
#include "CPathMgr.h"
#include "CKeyMgr.h"
#include "CLogMgr.h"

#include "CTexture.h"
#include "CNote.h"
#include "CSound.h"
#include "resource.h"
#include "CLevel.h"
#include "CEditorLevel.h"

#define GT (ULONGLONG)GEARLINE_TYPE
#define NOTE_MOVE_SECOND	200
#define GEAR_LINE_POS		650
#define BPM					(120.f / 105.f)

// 전역
int		minus = -1;
float	shineAlphaBuf = 0;
float	BPMLineCheckAcc = 0.f;


CGear::CGear()
	:m_blendFunc{}
	,m_GearBgTexture(nullptr)
	,m_CurMusicTime(0.f)
	,m_pMusic(nullptr)
	,m_iSpeed(10)
	,m_IsMusicPlaying(true)
	,m_MaxMusicTime(141.2f)
	,m_ButtonClickShine(nullptr)
	,m_GearClickShine(nullptr)
	,m_HpShine(nullptr)
{
	// blend function setting
	m_blendFunc.BlendOp = AC_SRC_OVER;
	m_blendFunc.BlendFlags = 0;
	m_blendFunc.AlphaFormat = AC_SRC_ALPHA; // 0
	m_blendFuncShine.BlendOp = AC_SRC_OVER;
	m_blendFuncShine.BlendFlags = 0;
	m_blendFuncShine.AlphaFormat = AC_SRC_ALPHA;
	m_blendFunc.SourceConstantAlpha = 255; // 0 ~ 255
	m_blendFuncShine.SourceConstantAlpha = 255; // 0 ~ 255
	SetPos(Vec2(50,0));

	// texture
	m_GearBgTexture = FINDTEX(L"gear_bg");
	m_SpeedTexture = FINDTEX(L"icon_speed_atlas");
	
	// 판정선을 가져올 게 아니라, 그냥 기어 프레임과 안 쪽 노트 부분을 구분해야겠는데?
	m_GearFrameTexture = FINDTEX(L"gear_default_frame");


	// shine Texture
	m_JudgeBarShine = FINDTEX(L"gear_shine_judgeline");
	m_ScoreShine = FINDTEX(L"gear_shine_score");
	m_BeltBarShine = FINDTEX(L"gear_shine_belt");
	//m_HpShine = FINDTEX(L"gear_bg");
	//m_ButtonClickShine = FINDTEX(L"gear_bg");
	//m_GearClickShine = FINDTEX(L"gear_bg");

	m_BPMLine = FINDTEX(L"gear_BPMline_white");
	m_vecBPMLineTimeBuf.resize(8);
	for (int i = 0; i < m_vecBPMLineTimeBuf.size(); ++i)
	{
		m_vecBPMLineTimeBuf[i] = BPM * i;
	}
}

CGear::~CGear()
{
}

void CGear::tick(float _DT)
{
	Super::tick(_DT);

#pragma region SHINE_ALPHA

	shineAlphaBuf += float(255 * minus * _DT);

	if (shineAlphaBuf < 0)
	{
		minus = 1;
		shineAlphaBuf = 0;
	}
	if (shineAlphaBuf > 255) 
	{
		minus = -1;
		shineAlphaBuf = 255;
	}

	m_blendFuncShine.SourceConstantAlpha = (BYTE)shineAlphaBuf;

#pragma endregion
		
#pragma region SPEED

	if (KEY_TAP(KEY::_1) || KEY_PRESSED(KEY::_1))
	{
		if (m_iSpeed != 10)
			--m_iSpeed;
	}

	if (KEY_TAP(KEY::_2) || KEY_PRESSED(KEY::_2))
	{
		if (m_iSpeed != 99)
			++m_iSpeed;
	}

#pragma endregion



#pragma region MUSIC
	// 음악 재생도 추가
	if (m_IsMusicPlaying) m_CurMusicTime += _DT;

	// 일시 정지, 재생
	if (KEY_TAP(KEY::SPACE))
	{
		if (m_IsMusicPlaying)	StopMusic();
		else					PlayMusic();
	}
#pragma endregion


#pragma region BPM_LINE_TIME_CHECK
	if (BPMLineCheckAcc > BPM)
	{
		float TimeBuf = m_vecBPMLineTimeBuf[m_vecBPMLineTimeBuf.size() - 1];
		m_vecBPMLineTimeBuf.push_back(TimeBuf + BPM);
		BPMLineCheckAcc = BPM - BPMLineCheckAcc;
	}
	BPMLineCheckAcc += _DT;
#pragma endregion
}

void CGear::render(HDC _dc)
{
	Vec2 vPos	= GetPos();
	Vec2 vScale = GetScale();

#pragma region GEAR_BG_RENDER
	if (nullptr != m_GearBgTexture)
	{
		POINT vImgScale = { (int)m_GearBgTexture->GetWidth(), (int)m_GearBgTexture->GetHeight() };
		AlphaBlend(_dc
			, int(vPos.x) + 50, int(vPos.y)
			, 418, 900
			, m_GearBgTexture->GetDC()
			, 0, 0
			, vImgScale.x, vImgScale.y
			, m_blendFunc);
	}
#pragma endregion

	float speed = (float)m_iSpeed / 10.f;

#pragma region BPM_LINE_RENDER

	POINT vSrc = { (int)m_BPMLine->GetWidth(), (int)m_BPMLine->GetHeight() };
	int XDest = 100;
	int YDest = 0;

	for (auto& iter : m_vecBPMLineTimeBuf)
	{
		YDest = int((m_CurMusicTime - iter) * (NOTE_MOVE_SECOND * speed)) + GEAR_LINE_POS;
		if (!(YDest > -50 && YDest < 750)) continue; // 기어 안에 없을 경우 render 건너뜀
		AlphaBlend(_dc
			, XDest, YDest
			, 420, 1
			, m_BPMLine->GetDC()
			, 0, 0
			, vSrc.x, vSrc.y
			, m_blendFunc);
	}
	
#pragma endregion

#pragma region NOTE_RENDER
	NoteRender(_dc, speed);
#pragma endregion


#pragma region GEAR_FRAME_RENDER
	// 기어 frame(tick에서 수행하는 프레임 말고 테두리 를 뜻하는 프레임) render
	if (nullptr != m_GearFrameTexture)
	{
		POINT vImgScale = { (int)m_GearFrameTexture->GetWidth(), (int)m_GearFrameTexture->GetHeight() };
		AlphaBlend(_dc
			, int(vPos.x), int(vPos.y)
			, int(vImgScale.x * 0.8333f), int(vImgScale.y * 0.8333f + 1)
			, m_GearFrameTexture->GetDC()
			, 0, 0
			, vImgScale.x, vImgScale.y
			, m_blendFunc);
	}
#pragma endregion

#pragma region SPEED_ICON_RENDER
	if (nullptr != m_SpeedTexture)
	{
		int SpeedTexPrintNo = m_iSpeed / 10;
		int renderSpeedIconX = 72 * (SpeedTexPrintNo - 1);
		//POINT vImgScale = { m_SpeedTexture->GetWidth(), m_SpeedTexture->GetHeight() };
		AlphaBlend(_dc
			, int(75 * 0.8333f + 50), int(1000 * 0.8333f)
			, int(72 * 0.8333f + 1), int(72 * 0.8333f + 1)
			, m_SpeedTexture->GetDC()
			, renderSpeedIconX, 0
			, 72, 72
			, m_blendFunc);
	}
#pragma endregion

#pragma region SHINE_EFFECT_RENDER
	// score shine
	if (nullptr != m_ScoreShine)
	{
		POINT vImgScale = { (int)m_ScoreShine->GetWidth(), (int)m_ScoreShine->GetHeight() };
		AlphaBlend(_dc
			, int(430 * 0.8333f + 50), int(965 * 0.8333f)
			, int(130 * 0.8333f), int(30 * 0.8333f)
			, m_ScoreShine->GetDC()
			, 0, 0
			, vImgScale.x, vImgScale.y
			, m_blendFuncShine);
	}

	// belt shine
	if (nullptr != m_BeltBarShine)
	{
		POINT vImgScale = { (int)m_BeltBarShine->GetWidth(), (int)m_BeltBarShine->GetHeight() };
		AlphaBlend(_dc
			, int(60 * 0.8333f + 50), int(955 * 0.8333f)
			, int(500 * 0.8333f), int(15 * 0.8333f)
			, m_BeltBarShine->GetDC()
			, 0, 0
			, vImgScale.x, vImgScale.y
			, m_blendFuncShine);
	}

	// judge line shine
	if (nullptr != m_JudgeBarShine)
	{
		POINT vImgScale = { (int)m_JudgeBarShine->GetWidth(), (int)m_JudgeBarShine->GetHeight() };
		AlphaBlend(_dc
			, int(60 * 0.8333f + 50), int(745 * 0.8333f)
			, int(500 * 0.8333f), int(20 * 0.8333f)
			, m_JudgeBarShine->GetDC()
			, 0, 0
			, vImgScale.x, vImgScale.y
			, m_blendFuncShine);
	}
#pragma endregion

	Super::render(_dc); // collider render
}



void CGear::StopMusic()
{
	m_IsMusicPlaying = false;
	m_pMusic->Stop();
}

void CGear::PlayMusic(int diff)
{
	m_IsMusicPlaying = true;
	m_CurMusicTime += diff;

	if (m_CurMusicTime < 0.f)
	{
		m_CurMusicTime = 0.f;
	}
	m_pMusic->SetPosition(m_CurMusicTime * 100.f / m_MaxMusicTime);
	
}



#undef GT

