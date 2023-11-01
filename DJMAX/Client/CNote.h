#pragma once
#include "CObj.h"

class CTexture;

class CNote
	:public CObj
{
	GENERATED_OBJECT(CObj);
private: // ���� ������� �ؾ� �ϴ� ���
	NOTE_TYPE		m_eType;		// if(m_type)���� ����ϸ� �ճ�Ʈ���� üũ ������ ��.
	float			m_fTapTime;		// tap �� �ð�(���� ���� ���൵�� ���� ��, 0.01�� ������ ���� ����)
	float			m_fPressTime;	// press�� �����ؾ� �ϴ� �ð�.
	GEARLINE_TYPE	m_Line;		// ���;� �ϴ� ����

private: // �ؽ��� 
	CTexture*	m_pNoteTexture;

public: // Get, Set �Լ�
	NOTE_TYPE	GetNoteType()	{ return m_eType; }
	float		GetNoteTap()	{ return m_fTapTime; }
	float		GetNotePress()	{ return m_fPressTime; }

	// �Լ��� y ���� �����ϴ� �Լ�...�Ƴ� �ʿ� ����.

	void		SetNoteType(NOTE_TYPE _eType)		{ m_eType = _eType; }
	void		SetNoteTap(float _fSetTapTime)		{ m_fTapTime = _fSetTapTime; }
	void		SetNotePress(float _fSetPressTime)	{ m_fPressTime = _fSetPressTime; }
	void		SetNoteLine(GEARLINE_TYPE _Line);

public:
	virtual void render(HDC _dc)	override;

public:
	CLONE(CNote);
	CNote();
	CNote(NOTE_TYPE _type , float _tapTime, float _pressTime, GEARLINE_TYPE _line);
	CNote(const CNote& _Origin);
	~CNote();

};