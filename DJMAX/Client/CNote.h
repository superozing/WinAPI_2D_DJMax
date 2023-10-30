#pragma once
#include "CObj.h"

class CNote
	:public CObj
{
	GENERATED_OBJECT(CObj);
private:
	NOTE_TYPE	m_eType;		// if(m_type)���� ����ϸ� �ճ�Ʈ���� üũ ������ ��.
	float		m_fTapTime;		// tap �� �ð�(���� ���� ���൵�� ���� ��, 0.01�� ������ ���� ����)

	float		m_fPressTime;	// press�� �����ؾ� �ϴ� �ð�.

public: // Get, Set �Լ�
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