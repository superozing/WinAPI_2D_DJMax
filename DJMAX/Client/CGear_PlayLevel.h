#pragma once
#include "CGear.h"
#include "CNote.h"
//#include "CJudgeTexture.h"
class CJudgeTexture;
class CNote;
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

    // ���� ���� �ʸ� ��� �ִ� �迭
    float               m_JudgeRange[(UINT)JUDGE_MODE::END];
    UINT                m_JudgeRangeIdx;

    CJudgeTexture*      m_JudgeTexture;
private:
    class CPlayLevel*   m_pOwnerLevel;
    vector<int>&        m_vecJudge;
public:
    virtual void LoadNoteData() override;


    virtual void tick(float _DT) override;
    virtual void render(HDC _dc) override;

    virtual void NoteRender(HDC _dc, float speed) override;

    NoteInfo GetNoteInfo();

private:
    bool JudgeCheck(JUDGE_PERCENT_CAL _Percent, float _JudgeMode, float _TapTime);
public:
    CGear_PlayLevel(vector<int>& _vecJudge, CJudgeTexture* _JudgeTexArr);
    ~CGear_PlayLevel();

    friend class CPlayLevel;
};

