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
	CTexture*		m_SpeedTexture; // ��Ʈ�� �������� �ӵ� ��Ʋ�󽺸� ��� �־�� �ϴµ�, �̷� ū ����� ������Ʈ�� ������� ���� ��.
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
	void DeleteNote(); // iterator �� ����Ű�� ���� ��Ʈ ����
	void EditNote(); // iterator �� ����Ű�� ���� ��Ʈ ���� (DialogBox()ȣ��)

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

