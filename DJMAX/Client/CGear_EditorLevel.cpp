#include "pch.h"
#include "CGear_EditorLevel.h"

#include "CEditorLevel.h"
#include "CPathMgr.h"
#include "CAssetMgr.h"
#include "CTexture.h"
#include "CNote.h"
#include "CKeyMgr.h"
#define GT (ULONGLONG)GEARLINE_TYPE
#define NOTE_MOVE_SECOND	180
#define GEAR_LINE_POS		650
#define BPM					(120.f / 105.f)

void AddNoteSec(GEARLINE_TYPE _line, CGear_EditorLevel* _owner);

CGear_EditorLevel::CGear_EditorLevel()
	: m_noteSecBufArr{}
{
	m_FocusCogwheelTexture = FINDTEX(L"톱니눌림");
}

CGear_EditorLevel::~CGear_EditorLevel()
{
}

void CGear_EditorLevel::tick(float _DT)
{
	CGear::tick(_DT);
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

#pragma region NOTE_EDIT
	if (KEY_TAP(KEY::UP))
	{
		m_vecNotes[m_FocusIdx].m_fTapTime -= 0.01f;
		m_vecNotes[m_FocusIdx].m_fReleasedTime -= 0.01f;
	}
	if (KEY_TAP(KEY::DOWN))
	{
		m_vecNotes[m_FocusIdx].m_fTapTime += 0.01f;
		m_vecNotes[m_FocusIdx].m_fReleasedTime += 0.01f;
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
}

void CGear_EditorLevel::render(HDC _dc)
{
	CGear::render(_dc);
	float speed = (float)m_iSpeed / 10.f;

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
}


// AddNoteSec()로부터만 호출 가능.
void CGear_EditorLevel::AddNote(NOTE_TYPE _type, float _tapTime, float _releasedTime, GEARLINE_TYPE _line)
{
	_tapTime = roundf(_tapTime * 100) / 100;
	_releasedTime = roundf(_releasedTime * 100) / 100;
	m_vecNotes.push_back(CNote(_type, _tapTime, _releasedTime, _line, this));
}

// iterator가 현재 가리키고 있는 노트를 지웁니당.
void CGear_EditorLevel::DeleteNote()
{ 
	auto iter = m_vecNotes.begin();
	for (int i = 0; i < m_FocusIdx; ++i)
		++iter;
	m_vecNotes.erase(iter);
}

// iterator가 현재 가리키고 있는 노트를 수정합니다.
void CGear_EditorLevel::EditNote()
{
	m_pOwner->OpenNoteEditWindow(&m_vecNotes[m_FocusIdx]);
}

void CGear_EditorLevel::SaveNoteData()
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
	if (_wfopen_s(&pFile, szFilePath, L"wb"))
		LOG(LOG_LEVEL::ERR, L"파일 열기에 실패했습니다..");


	// 타일 개수
	size_t sizeBuf = m_vecNotes.size();
	if (pFile)
		fwrite(&sizeBuf, sizeof(size_t), 1, pFile);

	for (auto& iter : m_vecNotes)
	{
		iter.Save(pFile);
	}


	if (pFile)
		fclose(pFile);
}


void NoteSec::AddNoteSec(GEARLINE_TYPE _line, CGear_EditorLevel* _owner)
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

