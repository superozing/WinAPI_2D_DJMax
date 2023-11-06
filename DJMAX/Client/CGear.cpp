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
#define NOTE_MOVE_SECOND	180
#define GEAR_LINE_POS		650
#define BPM					(120.f / 105.f)

// 전역
int		minus = -1;
float	shineAlphaBuf = 0;
float	BPMLineCheckAcc = 0.f;


CGear::CGear()
	:m_blendFunc{}
	,m_vecNotes()
	,m_GearBgTexture(nullptr)
	,m_AccMusicTime(0.f)
	,m_noteSecBufArr{}
	,m_pMusic(nullptr)
	,m_iSpeed(10)
	,m_IsMusicPlaying(true)
	,m_MaxMusicTime(141)
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

	m_FocusCogwheelTexture = FINDTEX(L"톱니눌림");

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

#pragma region NOTE_FOCUS
	// 
	if (KEY_TAP(KEY::LEFT))
	{
		if (m_FocusIdx != 0)
			--m_FocusIdx;
	}
	if (KEY_TAP(KEY::RIGHT))
	{
		if (m_FocusIdx < m_vecNotes.size())
			++m_FocusIdx;
	}
#pragma endregion

#pragma region MUSIC
	// 음악 재생도 추가
	if (m_IsMusicPlaying) m_AccMusicTime += _DT;

	// 일시 정지, 재생
	if (KEY_TAP(KEY::SPACE))
	{
		if (m_IsMusicPlaying)	StopMusic();
		else					PlayMusic();
	}
#pragma endregion

#pragma region NOTE_EDIT
	if (KEY_TAP(KEY::UP))
	{
		m_vecNotes[m_FocusIdx].m_fTapTime		-= 0.01f;
		m_vecNotes[m_FocusIdx].m_fReleasedTime	-= 0.01f;
	}
	if (KEY_TAP(KEY::DOWN))
	{
		m_vecNotes[m_FocusIdx].m_fTapTime		+= 0.01f;
		m_vecNotes[m_FocusIdx].m_fReleasedTime	+= 0.01f;
	}
	if (KEY_TAP(KEY::NUM9)) SaveNoteData();
	if (KEY_TAP(KEY::NUM6)) EditNote();
	if (KEY_TAP(KEY::NUM0)) DeleteNote();

#pragma endregion

#pragma region KEY_TAP_CHECK
	if (KEY_TAP(KEY::LSHIFT))	m_noteSecBufArr[GT::LEFTSIDE].tap = m_AccMusicTime;
	if (KEY_TAP(KEY::A))		m_noteSecBufArr[GT::_1].tap = m_AccMusicTime;
	if (KEY_TAP(KEY::S))		m_noteSecBufArr[GT::_2].tap = m_AccMusicTime;
	if (KEY_TAP(KEY::NUM1))		m_noteSecBufArr[GT::_3].tap = m_AccMusicTime;
	if (KEY_TAP(KEY::NUM2))		m_noteSecBufArr[GT::_4].tap = m_AccMusicTime;
	if (KEY_TAP(KEY::NUM3))		m_noteSecBufArr[GT::RIGHTSIDE].tap = m_AccMusicTime;
#pragma endregion
	
#pragma region KEY_RELEASED_CHECK
	if (KEY_RELEASED(KEY::LSHIFT))
	{
		m_noteSecBufArr[GT::LEFTSIDE].release = m_AccMusicTime;
		m_noteSecBufArr[GT::LEFTSIDE].AddNoteSec(GEARLINE_TYPE::LEFTSIDE, this);
	}
	if (KEY_RELEASED(KEY::A))
	{
		m_noteSecBufArr[GT::_1].release = m_AccMusicTime;
		m_noteSecBufArr[GT::_1].AddNoteSec(GEARLINE_TYPE::_1, this);
	}
	if (KEY_RELEASED(KEY::S))
	{
		m_noteSecBufArr[GT::_2].release = m_AccMusicTime;
		m_noteSecBufArr[GT::_2].AddNoteSec(GEARLINE_TYPE::_2, this);
	}
	if (KEY_RELEASED(KEY::NUM1))
	{
		m_noteSecBufArr[GT::_3].release = m_AccMusicTime;
		m_noteSecBufArr[GT::_3].AddNoteSec(GEARLINE_TYPE::_3, this);
	}
	if (KEY_RELEASED(KEY::NUM2))
	{
		m_noteSecBufArr[GT::_4].release = m_AccMusicTime;
		m_noteSecBufArr[GT::_4].AddNoteSec(GEARLINE_TYPE::_4, this);
	}
	if (KEY_RELEASED(KEY::NUM3))
	{
		m_noteSecBufArr[GT::RIGHTSIDE].release = m_AccMusicTime;
		m_noteSecBufArr[GT::RIGHTSIDE].AddNoteSec(GEARLINE_TYPE::RIGHTSIDE, this);
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
		POINT vImgScale = { m_GearBgTexture->GetWidth(), m_GearBgTexture->GetHeight() };
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

	POINT vSrc = { m_BPMLine->GetWidth(), m_BPMLine->GetHeight() };
	int XDest = 100;
	int YDest = 0;

	for (auto& iter : m_vecBPMLineTimeBuf)
	{
		YDest = int((m_AccMusicTime - iter) * (NOTE_MOVE_SECOND * speed)) + GEAR_LINE_POS;
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
	// 벡터 안의 모든 노트 render
	for (auto& iter : m_vecNotes)
	{
		iter.render(_dc, m_AccMusicTime, speed);
	}
#pragma endregion

#pragma region FOCUS_NOTE_RENDER
	// 포커싱 노트
	if (0 <= m_FocusIdx && m_vecNotes.size() > m_FocusIdx)
	{
		POINT vImgScale = { m_FocusCogwheelTexture->GetWidth(), m_FocusCogwheelTexture->GetHeight() };
		int xDest = int(m_vecNotes[m_FocusIdx].GetPos().x - 20);
		//int((_curTime - m_fReleasedTime) * (NOTE_MOVE_SECOND * _speed)) + GEAR_LINE_POS;
		int YDest = int((m_AccMusicTime - m_vecNotes[m_FocusIdx].m_fReleasedTime) * (NOTE_MOVE_SECOND * speed)) + GEAR_LINE_POS;
		AlphaBlend(_dc
			, xDest, YDest
			, 20, 20
			, m_FocusCogwheelTexture->GetDC()
			, 0, 0
			, vImgScale.x, vImgScale.y
			, m_blendFunc);
	}
#pragma endregion

#pragma region GEAR_FRAME_RENDER
	// 기어 frame(tick에서 수행하는 프레임 말고 테두리 를 뜻하는 프레임) render
	if (nullptr != m_GearFrameTexture)
	{
		POINT vImgScale = { m_GearFrameTexture->GetWidth(), m_GearFrameTexture->GetHeight() };
		AlphaBlend(_dc
			, int(vPos.x), int(vPos.y)
			, vImgScale.x * 0.8333f, vImgScale.y * 0.8333f + 1
			, m_GearFrameTexture->GetDC()
			, 0, 0
			, vImgScale.x, vImgScale.y
			, m_blendFunc);
	}
#pragma endregion

#pragma region SPEED_ICON_RENDER
	if (nullptr != m_SpeedTexture)
	{
		int SpeedTexPrintNo = int(m_iSpeed / 10);
		POINT vImgScale = { m_SpeedTexture->GetWidth(), m_SpeedTexture->GetHeight() };
		AlphaBlend(_dc
			, 75 * 0.8333f + 50, 1000 * 0.8333f
			, 72 * 0.8333f + 1, 72 * 0.8333f + 1
			, m_SpeedTexture->GetDC()
			, (SpeedTexPrintNo - 1) * 72, 0
			, SpeedTexPrintNo * 72, 72
			, m_blendFunc);
	}
#pragma endregion

#pragma region SHINE_EFFECT_RENDER
	// score shine
	if (nullptr != m_ScoreShine)
	{
		POINT vImgScale = { m_ScoreShine->GetWidth(), m_ScoreShine->GetHeight() };
		AlphaBlend(_dc
			, 430 * 0.8333 + 50, 965 * 0.8333
			, 130 * 0.8333, 30 * 0.8333
			, m_ScoreShine->GetDC()
			, 0, 0
			, vImgScale.x, vImgScale.y
			, m_blendFuncShine);
	}

	// belt shine
	if (nullptr != m_BeltBarShine) // 만약에 m_BeltBarShine이게 아무것도 없다면 
	{
		POINT vImgScale = { m_BeltBarShine->GetWidth(), m_BeltBarShine->GetHeight() };
		AlphaBlend(_dc
			, 60 * 0.8333 + 50, 955 * 0.8333
			, 500 * 0.8333, 15 * 0.8333
			, m_BeltBarShine->GetDC()
			, 0, 0
			, vImgScale.x, vImgScale.y
			, m_blendFuncShine);
	}

	// judge line shine
	if (nullptr != m_JudgeBarShine) // 만약에 m_BeltBarShine이게 아무것도 없다면 
	{
		POINT vImgScale = { m_JudgeBarShine->GetWidth(), m_JudgeBarShine->GetHeight() };
		AlphaBlend(_dc
			, 60 * 0.8333 + 50, 745 * 0.8333
			, 500 * 0.8333, 20 * 0.8333
			, m_JudgeBarShine->GetDC()
			, 0, 0
			, vImgScale.x, vImgScale.y
			, m_blendFuncShine);
	}
#pragma endregion

	Super::render(_dc); // collider render
}

// AddNoteSec()로부터만 호출 가능.
void CGear::AddNote(NOTE_TYPE _type, float _tapTime, float _releasedTime, GEARLINE_TYPE _line)
{
	_tapTime = roundf(_tapTime * 100) / 100;
	_releasedTime = roundf(_releasedTime * 100) / 100;
	m_vecNotes.push_back(CNote(_type, _tapTime, _releasedTime, _line, this));
}

// iterator가 현재 가리키고 있는 노트를 지웁니당.
void CGear::DeleteNote()
{
	m_vecNotes.erase(m_vecNotes.begin() + m_FocusIdx--);
}

// iterator가 현재 가리키고 있는 노트를 수정합니다.
void CGear::EditNote()
{
	m_pOwner->OpenNoteEditWindow(&m_vecNotes[m_FocusIdx]);
}

void CGear::LoadNoteData()
{
	// open a file name
	OPENFILENAME ofn = {};

	wstring strTileFolderPath = CPathMgr::GetContentPath();
	strTileFolderPath += L"note\\";

	wchar_t szFilePath[256] = {};

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFilePath;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = 256;
	ofn.lpstrFilter = L"Note\0*.note\0ALL\0*.*";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = strTileFolderPath.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (false == GetOpenFileName(&ofn))
		return;


	FILE* pFile = nullptr;
	if (_wfopen_s(&pFile, szFilePath, L"rb")) 
		LOG(LOG_LEVEL::ERR, L"파일 열기에 실패했습니다..");

	// 노트 개수
	size_t sizeBuf = 0;
	if (pFile) 
		fread(&sizeBuf, sizeof(size_t), 1, pFile);

	m_vecNotes.reserve(sizeBuf);

	for (size_t i = 0; i < sizeBuf; ++i)
	{
		CNote newdata;
		m_vecNotes.push_back(newdata.Load(pFile, this));
	}

	if (pFile)
	{
		fclose(pFile);
		m_FocusIdx = 0;
	}

}

void CGear::SaveNoteData()
{
	// open a file name
	OPENFILENAME ofn = {};

	wstring strTileFolderPath = CPathMgr::GetContentPath();
	strTileFolderPath += L"note\\";

	wchar_t szFilePath[256] = {};

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFilePath;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = 256;
	ofn.lpstrFilter = L"Note\0*.note\0ALL\0*.*";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = strTileFolderPath.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (false == GetSaveFileName(&ofn))
		return;

	FILE* pFile = nullptr;
	if(_wfopen_s(&pFile, szFilePath, L"wb")) 
		LOG(LOG_LEVEL::ERR, L"파일 열기에 실패했습니다..");


	// 타일 개수
	size_t sizeBuf = m_vecNotes.size();
	if (pFile) 
		fwrite(&sizeBuf, sizeof(size_t), 1, pFile);

	for (auto& iter: m_vecNotes)
	{
		iter.Save(pFile);
	}


	if (pFile) 
		fclose(pFile);
}

void CGear::StopMusic()
{
	m_IsMusicPlaying = false;
	m_pMusic->Stop();
}

void CGear::PlayMusic()
{
	m_IsMusicPlaying = true;
	m_pMusic->SetPosition(m_AccMusicTime * 100.f / m_MaxMusicTime);
}

void NoteSec::AddNoteSec(GEARLINE_TYPE _line, CGear* _owner)
{
	// 현재 노트가 사이드 트랙 노트인데 0.25초 이상 눌리지 않았을 경우
	if ((_line == GEARLINE_TYPE::LEFTSIDE || _line == GEARLINE_TYPE::RIGHTSIDE) && this->NoteTimeDiff() < 0.25f)
		return;

	// 사이드트랙 노트
	if ((_line == GEARLINE_TYPE::LEFTSIDE || _line == GEARLINE_TYPE::RIGHTSIDE) && this->NoteTimeDiff() > 0.25f)
		_owner->AddNote(NOTE_TYPE::SIDETRACK, this->tap, this->release, _line);

	// 기본 노트
	else if (!(_line == GEARLINE_TYPE::LEFTSIDE) && !(_line == GEARLINE_TYPE::RIGHTSIDE) && this->NoteTimeDiff() < 0.25f)
		_owner->AddNote(NOTE_TYPE::DEFAULT, this->tap, this->tap, _line);

	// 롱 노트
	else if (!(_line == GEARLINE_TYPE::LEFTSIDE) && !(_line == GEARLINE_TYPE::RIGHTSIDE) && this->NoteTimeDiff() > 0.25f)
		_owner->AddNote(NOTE_TYPE::LONG, this->tap, this->release, _line);

	this->tap = 0.f;
	this->release = 0.f;
}

#undef GT

