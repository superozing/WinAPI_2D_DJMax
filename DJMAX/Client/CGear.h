#pragma once
#include "CObj.h"


class CNote;
class CSound;

class CGear :
    public CObj
{
	GENERATED_OBJECT(CObj);
public:
	CTexture*		m_GearTexture;
	CTexture*		m_GearJudgeLine;
	//CTexture*		m_NoteSpeed; // ��Ʈ�� �������� �ӵ� ��Ʋ�󽺸� ��� �־�� �ϴµ�, �̷� ū ����� ������Ʈ�� ������� ���� ��.
	CSound*			m_pMusic;

	vector<CNote>	m_vecNotes;
	BLENDFUNCTION	m_blendFunc;

private:
	virtual void tick(float _DT) override;
	virtual void render(HDC _dc) override;


public:
	void AddNote(NOTE_TYPE _type, float _tapTime, float _pressTime, GEARLINE_TYPE _line);

	virtual void LoadNoteData();
	virtual void SaveNoteData();

	CSound* GetSound() { return m_pMusic; }
public:
	CLONE_DISABLE(CGear);
	CGear();
	CGear(const CGear& _Origin) = delete;
	virtual ~CGear();

	friend class CNote;
};
