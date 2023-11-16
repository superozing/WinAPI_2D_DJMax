#pragma once
#include "CGear.h"
#include "CNote.h"


// ���� ����. include�� cpp �� ����
class CJudgeTexture;
class CLineShine;
class CCoolbomb;
class CNote;

class CCombo;
class CFever;


// ���� ���� + ��Ʈ ����
struct sNote
{
    bool    isJudged; // true �� tick���� ���ο� ��Ʈ ������ �Է� ����.
    CNote*   Note;
public:
    sNote()
        :isJudged(false)
    {
        Note = new CNote;
    }
    friend class CGear_PlayLevel;

};

// ��Ʈ ���� ����
struct NoteInfo
{
    float			m_fTapTime;		// tap �� �ð�(���� ���� ���൵�� ���� ��, 0.01�� ������ ���� ����)
    float			m_fReleasedTime;// press�� �����ؾ� �ϴ� �ð�.
    NOTE_TYPE		m_eType;		// if(m_type)���� ����ϸ� �ճ�Ʈ���� üũ ������ ��.
    GEARLINE_TYPE	m_Line;

public:
    NoteInfo& Load(FILE* _pFile);

public:
};

// Ű �Է� ó���� ���� Ű ���� ���� ����ü
struct KeyState
{
    bool key_tap;
    bool key_press;
    bool key_release;

public:
    bool isTap()        { return key_tap; }
    bool isPress()      { return key_press; }
    bool isRelease()    { return key_release; }
};

class CGear_PlayLevel
     : public CGear
{
private: // �޸� Ǯ
    vector<sNote*>      m_vecNotePool;
    vector<NoteInfo>    m_vecNoteInfo;
    UINT                m_NoteInfoIdx;

private:
    KeyState           m_KeyCheck[(ULONGLONG)GEARLINE_TYPE::END];
    void KeyCheck(GEARLINE_TYPE _line, KEY _key);

    void JudgementOperation(JUDGE_VECTOR_IDX _Judge, CNote* CurNote);

    // ���� ���� �ʸ� ��� �ִ� �迭
    float               m_JudgeRange[(UINT)JUDGE_MODE::END];
    UINT                m_JudgeRangeIdx;

    CJudgeTexture*      m_JudgeTexture;
    CLineShine*         m_LineTexture;
    CCoolbomb*          m_Coolbomb;
private:
    float               m_DelayOffset;
public:
    void SetDelayOffset(float _delay) { m_DelayOffset = _delay; }

private:
    CCombo*             m_Combo;
    CFever*             m_Fever;

private:
    class CPlayLevel*   m_pOwnerLevel;
    vector<int>&        m_vecJudge;
public:
    virtual void LoadNoteData() override;

    virtual void tick(float _DT) override;
    virtual void render(HDC _dc) override;

    virtual void GearInsideRender(HDC _dc, float speed) override;

    NoteInfo GetNoteInfo();

private:
    JUDGE_VECTOR_IDX JudgeCheck(float _TapTime);

public:
    CGear_PlayLevel(vector<int>& _vecJudge, CJudgeTexture* _JudgeTexture, CLineShine* _LineTexture
        , CCoolbomb* _CoolbombTexture, CCombo* _Combo, CFever* _Fever);
    ~CGear_PlayLevel();

    friend class CPlayLevel;
    friend class CGear_PlayLevel;
};

