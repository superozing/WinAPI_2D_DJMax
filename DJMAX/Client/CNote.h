#pragma once
#include "CObj.h"

class CTexture;
class CGear;

class CNote
	:public CObj
{
	GENERATED_OBJECT(CObj);
private: // 파일 입출력을 해야 하는 멤버
	float			m_fTapTime;		// tap 할 시간(현재 음악 진행도와 비교할 것, 0.01초 단위로 수정 가능)
	float			m_fReleasedTime;	// press를 지속해야 하는 시간.
	NOTE_TYPE		m_eType;		// if(m_type)같이 사용하면 롱노트인지 체크 가능할 듯.
	GEARLINE_TYPE	m_Line;			// 나와야 하는 라인

private: // 텍스쳐 
	CTexture*	m_pNoteTexture;
	BLENDFUNCTION	m_blendFunc;

private: // 기어
	CGear* m_pOwner;

public: // Get, Set 함수
	NOTE_TYPE	GetNoteType()	{ return m_eType; }
	float		GetNoteTapTime()	{ return m_fTapTime; }
	float		GetNoteReleasedTime()	{ return m_fReleasedTime; }
	GEARLINE_TYPE GetLineType() { return m_Line; }

	void		SetNoteType(NOTE_TYPE _eType)		{ m_eType = _eType; }
	void		SetNoteTapTime(float _fSetTapTime)		{ m_fTapTime = _fSetTapTime; }
	void		SetNoteReleasedTime(float _fSetPressTime)	{ m_fReleasedTime = _fSetPressTime; }
	void		SetNoteLine(GEARLINE_TYPE _Line);

public:
	void Save(FILE* _pFile);
	CNote& Load(FILE* _pFile, CGear* _owner);

public:
	virtual void render(HDC _dc, float _curTime, float _speed);

public:
	void operator = (const CNote& _other)
	{
		m_eType = _other.m_eType;
		m_fTapTime = _other.m_fTapTime;
		m_fReleasedTime = _other.m_fReleasedTime;
		m_Line = _other.m_Line;
		m_pOwner = _other.m_pOwner;
		SetNoteLine(m_Line);
		// blend function setting
		m_blendFunc.BlendOp = AC_SRC_OVER;
		m_blendFunc.BlendFlags = 0;

		m_blendFunc.SourceConstantAlpha = 255; // 0 ~ 255
		m_blendFunc.AlphaFormat = AC_SRC_ALPHA; // 0
	}

public:
	CLONE(CNote);
	CNote();
	CNote(NOTE_TYPE _type , float _tapTime, float _pressTime, GEARLINE_TYPE _line, CGear* _owner);
	CNote(const CNote& _Origin);
	~CNote();

	friend class CGear;
	friend class CGear_EditorLevel;
};