#pragma once
#include "CObj.h"


class CNote;
class CSound;
class CGear;

struct NoteSec
{
	float			tap;
	float			release;

public:
	float NoteTimeDiff() { return release - tap; }
	void AddNoteSec(GEARLINE_TYPE _line, CGear* _owner);

};






class CGear :
    public CObj
{
	GENERATED_OBJECT(CObj);
public:
	CTexture*		m_GearTexture;
	CTexture*		m_GearJudgeLine;
	//CTexture*		m_NoteSpeed; // 노트가 내려오는 속도 아틀라스를 들고 있어야 하는데, 이런 큰 기능은 오브젝트로 만드느게 좋을 듯.
	CSound*			m_pMusic;
	NoteSec			m_noteSecBufArr[(ULONGLONG)GEARLINE_TYPE::END];
	vector<CNote>	m_vecNotes;
	BLENDFUNCTION	m_blendFunc;

	float			m_AccMusicTime;
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
	friend struct NoteInfo;
};

