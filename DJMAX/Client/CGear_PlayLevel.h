#pragma once
#include "CGear.h"
#include "CNote.h"


// ���� ����. include�� cpp �� ����
class CJudgeTexture;
class CLineShine;
class CCoolbomb;
class CNote;
class CEffectAnim;
class CPlayLevel;
class CCombo;
class CFever;

class CSound;

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

struct LongNoteInfoBuffer
{
    float AccTime;
    bool isJudging;
    JUDGE_VECTOR_IDX judge;
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
private: 
    
    // �޸� Ǯ
    vector<sNote*>      m_vecNotePool;
    vector<NoteInfo>    m_vecNoteInfo; // ��Ʈ ���� �迭
    UINT                m_CurNoteInfoIdx; // ���� ��Ʈ ���� �ε���

    // Ű �Է� ó��
    KeyState            m_KeyCheck[(ULONGLONG)GEARLINE_TYPE::END];

    // ���� ������ ��� �ִ� �迭
    float               m_JudgeRange[(UINT)JUDGE_MODE::END];
    // 0~2���� 3�ܰ�� �̷����. ���� ���� �ε����� ���� ���� ������.
    UINT                m_JudgeRangeIdx; 

    // ��� �ؽ���
    CJudgeTexture*      m_JudgeTexture; // ���� �ؽ�Ʈ �̹���
    CLineShine*         m_LineTexture; // Ű �Է½� ���� ��¦��
    CCoolbomb*          m_Coolbomb; 
    CCombo*             m_Combo;
    CFever*             m_Fever;

    CPlayLevel*         m_pOwnerLevel; // �� ������ �÷��� ����
    vector<int>*        m_vecJudge;    // �÷��� ������ ������ ���� �迭
    

    // ��Ʈ ������
    float               m_DelayOffset;


    // �÷��� ���� ����
    CSound*             m_ClearSound;   // Ŭ���� ����
    PLAY_RESULT         playResult;     // �÷��� ��� enum ��(EndFlare render ���� Ʈ����)
    bool                EndTextureRender; // ���� ����� ���� render ����
    CTexture*           m_EndAtlas;     // �ƽ� �޺��� ����Ʈ �÷���
    CTexture*           m_EndFlare;     // ���


public:
    // ��Ʈ ��� ������ ����
    void SetDelayOffset(float _delay) { m_DelayOffset = _delay; }

    // Select Level���� ������ MUSICINFO�� ���� ��Ʈ ������ �ҷ�����
    virtual void LoadNoteData() override;

    //void PlayMusic(int diff = 0) override;

    //
    void init();

    virtual void tick(float _DT) override;
    virtual void render(HDC _dc) override;

    // �÷��� ���� ���� �� render�� ���߾�� �� ������Ʈ �鿡�� ����
    void EndRender(HDC _dc);

    // ��� ������ �� �ʿ� render �Ǿ�� �� ��� �� �Լ� �ȿ� �ֱ�. 
    virtual void GearInsideRender(HDC _dc, float speed) override;

    // ��Ʈ ������ ��������
    NoteInfo GetNoteInfo();

private:
    // ��Ʈ�� ���� üũ. ��ȯ���δ� ���� enum class ���� ������
    JUDGE_VECTOR_IDX JudgeCheck(float _TapTime);

    // �� ƽ���� Ű �Է��� üũ �� ����
    void KeyCheck(GEARLINE_TYPE _line, KEY _key);

    // ���� �� �ؾ� �� �۾� (���� ���Ϳ� ���� ���, ���� �ؽ�Ʈ �̹��� �ִϸ��̼�, Fever�� Combo ����)
    void JudgementOperation(JUDGE_VECTOR_IDX _Judge, CNote* CurNote);

public: // ������, �Ҹ���
    CGear_PlayLevel(vector<int>* _vecJudge, CJudgeTexture* _JudgeTexture, CLineShine* _LineTexture, CCoolbomb* _CoolbombTexture, CCombo* _Combo, CFever* _Fever);
    ~CGear_PlayLevel();

    friend class CPlayLevel;
    friend class CGear_PlayLevel;
};

