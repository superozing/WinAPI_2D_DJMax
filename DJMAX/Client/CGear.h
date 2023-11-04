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
public: // Texture
	CTexture*		m_GearTexture;
	CTexture*		m_SpeedTexture; // 노트가 내려오는 속도 아틀라스를 들고 있어야 하는데, 이런 큰 기능은 오브젝트로 만드느게 좋을 듯.
	CTexture*		m_GearJudgeLine;
	CTexture*		m_FocusCogwheelTexture;
	
public: // Note
	CSound*			m_pMusic;
	
	NoteSec			m_noteSecBufArr[(ULONGLONG)GEARLINE_TYPE::END];
	vector<CNote>	m_vecNotes;
	int				m_FocusIdx;

public: // Speed
	float			m_AccMusicTime;
	float			m_MaxMusicTime;
	bool			m_IsMusicPlaying;
	int				m_iSpeed;
	
public: // AlphaBlend
	BLENDFUNCTION	m_blendFunc;

public:
	void AddNote(NOTE_TYPE _type, float _tapTime, float _pressTime, GEARLINE_TYPE _line);
	void DeleteNote(); // iterator 가 가리키는 현재 노트 삭제
	void EditNote(); // iterator 가 가리키는 현재 노트 수정 (DialogBox()호출)

	void LoadNoteData();
	void SaveNoteData();

	CSound* GetSound() { return m_pMusic; }

	void StopMusic();
	void PlayMusic();

private:
	virtual void tick(float _DT) override;
	virtual void render(HDC _dc) override;


public:
	CLONE_DISABLE(CGear);
	CGear();
	CGear(const CGear& _Origin) = delete;
	virtual ~CGear();

	friend class CNote;
	friend struct NoteInfo;
};

