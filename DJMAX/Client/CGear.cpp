#include "pch.h"
#include "CGear.h"

#include "CAssetMgr.h"
#include "CTimeMgr.h"
#include "CPathMgr.h"
#include "CKeyMgr.h"

#include "CTexture.h"
#include "CNote.h"
#include "CSound.h"
#include "resource.h"
#include "CLevel.h"


#define GT (ULONGLONG)GEARLINE_TYPE

//using ::GEARLINE_TYPE;
CGear::CGear()
	:m_blendFunc{}
	,m_vecNotes()
	,m_GearTexture(nullptr)
	,m_AccMusicTime(0.f)
	,m_noteSecBufArr{}
	,m_pMusic(nullptr)
	,m_iSpeed(10)
{
	// blend function setting
	m_blendFunc.BlendOp = AC_SRC_OVER;
	m_blendFunc.BlendFlags = 0;

	m_blendFunc.SourceConstantAlpha = 255; // 0 ~ 255
	m_blendFunc.AlphaFormat = AC_SRC_ALPHA; // 0
	
	// texture
	m_GearTexture = FINDTEX(L"gear_default");
	SetPos(Vec2(50,-13));

	// 판정선을 가져올 게 아니라, 그냥 기어 프레임과 안 쪽 노트 부분을 구분해야겠는데?
	m_GearJudgeLine = FINDTEX(L"판정선");

}

CGear::~CGear()
{
}

void CGear::tick(float _DT)
{
	Super::tick(_DT);
	m_AccMusicTime += DT;
#pragma region SPEED
	if (KEY_TAP(KEY::_1)|| KEY_PRESSED(KEY::_1))
		--m_iSpeed;
	if (KEY_TAP(KEY::_2)|| KEY_PRESSED(KEY::_2))
		++m_iSpeed;
#pragma endregion

#pragma region KEY_TAP_CHECK
	if (KEY_TAP(KEY::LSHIFT))
		m_noteSecBufArr[GT::LEFTSIDE].tap = m_AccMusicTime;
	if (KEY_TAP(KEY::A))
		m_noteSecBufArr[GT::_1].tap = m_AccMusicTime;
	if (KEY_TAP(KEY::S))
		m_noteSecBufArr[GT::_2].tap = m_AccMusicTime;
	if (KEY_TAP(KEY::NUM1))
		m_noteSecBufArr[GT::_3].tap = m_AccMusicTime;
	if (KEY_TAP(KEY::NUM2))
		m_noteSecBufArr[GT::_4].tap = m_AccMusicTime;
	if (KEY_TAP(KEY::NUM3))
		m_noteSecBufArr[GT::RIGHTSIDE].tap = m_AccMusicTime;
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

	if (KEY_TAP(KEY::NUM9))
	{
		SaveNoteData();
	}
	
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

	float speed = (float)m_iSpeed / 10.f;
	for (auto& iter : m_vecNotes)
	{
		iter.render(_dc, m_AccMusicTime, speed);
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

void CGear::AddNote(NOTE_TYPE _type, float _tapTime, float _releasedTime, GEARLINE_TYPE _line)
{
	m_vecNotes.push_back(CNote(_type, _tapTime, _releasedTime, _line, this));
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
		fclose(pFile);
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

void NoteSec::AddNoteSec(GEARLINE_TYPE _line, CGear* _owner)
{
	// 현재 노트가 사이드 트랙 노트인데 0.25초 이상 눌리지 않았을 경우
	if ((_line == GEARLINE_TYPE::LEFTSIDE || _line == GEARLINE_TYPE::RIGHTSIDE) && this->NoteTimeDiff() < 0.25f)
		return;

	// 사이드트랙 노트
	if ((_line == GEARLINE_TYPE::LEFTSIDE || _line == GEARLINE_TYPE::RIGHTSIDE) && this->NoteTimeDiff() > 0.25f)
		_owner->AddNote(NOTE_TYPE::SIDETRACT, this->tap, this->release, _line);

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

