#pragma once
#include "CGear.h"
#include "CNote.h"


// 전방 선언만. include는 cpp 쪽 에서
class CJudgeTexture;
class CLineShine;
class CCoolbomb;
class CNote;

class CCombo;
class CFever;


// 판정 여부 + 노트 정보
struct sNote
{
    bool    isJudged; // true 시 tick에서 새로운 노트 정보를 입력 받음.
    CNote*   Note;
public:
    sNote()
        :isJudged(false)
    {
        Note = new CNote;
    }
    friend class CGear_PlayLevel;

};

// 노트 정보 저장
struct NoteInfo
{
    float			m_fTapTime;		// tap 할 시간(현재 음악 진행도와 비교할 것, 0.01초 단위로 수정 가능)
    float			m_fReleasedTime;// press를 지속해야 하는 시간.
    NOTE_TYPE		m_eType;		// if(m_type)같이 사용하면 롱노트인지 체크 가능할 듯.
    GEARLINE_TYPE	m_Line;

public:
    NoteInfo& Load(FILE* _pFile);

public:
};

// 키 입력 처리를 위한 키 정보 저장 구조체
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
private: // 메모리 풀
    vector<sNote*>      m_vecNotePool;
    vector<NoteInfo>    m_vecNoteInfo;
    UINT                m_NoteInfoIdx;

private:
    KeyState           m_KeyCheck[(ULONGLONG)GEARLINE_TYPE::END];
    void KeyCheck(GEARLINE_TYPE _line, KEY _key);

    void JudgementOperation(JUDGE_VECTOR_IDX _Judge, CNote* CurNote);

    // 판정 범위 초를 담고 있는 배열
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

