#pragma once
#include "CObj.h"


class CNote;
class CSound;
class CGear;
class CEditorLevel;



// ����: 60 / BPM, 


class CGear :
    public CObj
{
	GENERATED_OBJECT(CObj);
public: // Texture
	CTexture*		m_GearBgTexture;
	CTexture*		m_SpeedTexture; // ��Ʈ�� �������� �ӵ� ��Ʋ�󽺸� ��� �־�� �ϴµ�, �̷� ū ����� ������Ʈ�� ������� ���� ��.
	CTexture*		m_GearFrameTexture;
	//CTexture*		m_FocusCogwheelTexture;
	
public: // shine Texture
	CTexture*		m_JudgeBarShine;
	CTexture*		m_BeltBarShine;
	CTexture*		m_ScoreShine;
	CTexture*		m_HpShine;
	CTexture*		m_ButtonClickShine;
	CTexture*		m_GearClickShine;
	
	CTexture*		m_BPMLine;
	BLENDFUNCTION	m_blendFuncShine;


public: // Note
	CSound*			m_pMusic;
	
	//NoteSec			m_noteSecBufArr[(ULONGLONG)GEARLINE_TYPE::END];
	//int				m_FocusIdx;

public: // Speed
	float			m_CurMusicTime;
	float			m_MaxMusicTime;
	bool			m_IsMusicPlaying;
	int				m_iSpeed;
	vector<float>	m_vecBPMLineTimeBuf;

public: // AlphaBlend
	BLENDFUNCTION	m_blendFunc;

public:
	virtual void LoadNoteData() {}


public:
	CSound* GetSound() { return m_pMusic; }
public: // sound
	void StopMusic();
	void PlayMusic(int diff = 0);

protected:
	virtual void tick(float _DT) override;
	virtual void render(HDC _dc) override;
	virtual void NoteRender(HDC _dc, float speed) {}

public:
	CLONE_DISABLE(CGear);
	CGear();
	CGear(const CGear& _Origin) = delete;
	virtual ~CGear();

	friend class CNote;
	friend struct NoteInfo;
};

