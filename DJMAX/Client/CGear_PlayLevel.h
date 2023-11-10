#pragma once
#include "CGear.h"
#include "CNote.h"

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

// Ű �Է� ó���� ���� Ű �Է� ���� ���� ����ü
struct KeySecond
{
    float			tap;
    float			release;

public:
    float NoteTimeDiff() { return release - tap; }
};

class CGear_PlayLevel :
    public CGear
{
private:
    vector<sNote*>      m_vecNotePool;
    vector<NoteInfo>    m_vecNoteInfo;
    UINT                m_NoteInfoIdx;

private:
    KeySecond           m_KeyCheck[(ULONGLONG)GEARLINE_TYPE::END];

    // ���� ���� �ʸ� ��� �ִ� �迭
    float               m_JudgeRange[(UINT)JUDGE_MODE::END];
    UINT                m_JudgeRangeIdx;

public:
    virtual void LoadNoteData() override;

    virtual void tick(float _DT) override;
    virtual void render(HDC _dc) override;

    virtual void NoteRender(HDC _dc, float speed) override;

    NoteInfo GetNoteInfo();

private:
    bool JudgeCheck(JUDGE_PERCENT _Percent, float _JudgeMode, float _TapTime);
public:
    CGear_PlayLevel();
    ~CGear_PlayLevel();
};

