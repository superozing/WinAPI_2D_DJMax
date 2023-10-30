#pragma once
#include "CObj.h"

class CNote
	:public CObj
{
	GENERATED_OBJECT(CObj);
private:
	NOTE_TYPE	m_eType;		// if(m_type)같이 사용하면 롱노트인지 체크 가능할 듯.
	float		m_fTapTime;		// tap 할 시간(현재 음악 진행도와 비교할 것, 0.01초 단위로 수정 가능)

	float		m_fPressTime;	// press를 지속해야 하는 시간.

public: // Get, Set 함수
	NOTE_TYPE	GetNoteType()	{ return m_eType; }
	float		GetNoteTap()	{ return m_fTapTime; }
	float		GetNotePress()	{ return m_fPressTime; }

	void		SetNoteType(NOTE_TYPE _eType)		{ m_eType = _eType; }
	void		SetNoteTap(float _fSetTapTime)		{ m_fTapTime = _fSetTapTime; }
	void		SetNotePress(float _fSetPressTime)	{ m_fPressTime = _fSetPressTime; }

public:
	virtual void begin()			override;
	virtual void tick(float _DT)	override;
	virtual void render(HDC _dc)	override;

public:
	CNote();
	~CNote();

};