#pragma once
#include "CGear.h"
#include "CNote.h"


// 전방 선언만. include는 cpp 쪽 에서
class CJudgeTexture;
class CLineShine;
class CCoolbomb;
class CNote;
class CEffectAnim;
class CPlayLevel;
class CCombo;
class CFever;

class CSound;

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

struct LongNoteInfoBuffer
{
    float AccTime;
    bool isJudging;
    JUDGE_VECTOR_IDX judge;
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
private: 
    
    // 메모리 풀
    vector<sNote*>      m_vecNotePool;
    vector<NoteInfo>    m_vecNoteInfo; // 노트 정보 배열
    UINT                m_CurNoteInfoIdx; // 현재 노트 정보 인덱스

    // 키 입력 처리
    KeyState            m_KeyCheck[(ULONGLONG)GEARLINE_TYPE::END];

    // 판정 범위를 담고 있는 배열
    float               m_JudgeRange[(UINT)JUDGE_MODE::END];
    // 0~2까지 3단계로 이루어짐. 판정 범위 인덱스에 따라 범위 조절됨.
    UINT                m_JudgeRangeIdx; 

    // 기어 텍스쳐
    CJudgeTexture*      m_JudgeTexture; // 판정 텍스트 이미지
    CLineShine*         m_LineTexture; // 키 입력시 라인 반짝임
    CCoolbomb*          m_Coolbomb; 
    CCombo*             m_Combo;
    CFever*             m_Fever;

    CPlayLevel*         m_pOwnerLevel; // 기어를 소유한 플레이 레벨
    vector<int>*        m_vecJudge;    // 플레이 레벨이 소유한 판정 배열
    

    // 노트 딜레이
    float               m_DelayOffset;


    // 플레이 레벨 종료
    CSound*             m_ClearSound;   // 클리어 사운드
    PLAY_RESULT         playResult;     // 플레이 결과 enum 값(EndFlare render 여부 트리거)
    bool                EndTextureRender; // 판정 결과에 따른 render 여부
    CTexture*           m_EndAtlas;     // 맥스 콤보와 퍼펙트 플레이
    CTexture*           m_EndFlare;     // 배경


public:
    // 노트 출력 오프셋 설정
    void SetDelayOffset(float _delay) { m_DelayOffset = _delay; }

    // Select Level에서 설정한 MUSICINFO에 따른 노트 데이터 불러오기
    virtual void LoadNoteData() override;

    //void PlayMusic(int diff = 0) override;

    //
    void init();

    virtual void tick(float _DT) override;
    virtual void render(HDC _dc) override;

    // 플레이 레벨 종료 시 render를 멈추어야 할 오브젝트 들에게 선언
    void EndRender(HDC _dc);

    // 기어 프레임 안 쪽에 render 되어야 할 경우 이 함수 안에 넣기. 
    virtual void GearInsideRender(HDC _dc, float speed) override;

    // 노트 정보를 가져오기
    NoteInfo GetNoteInfo();

private:
    // 노트의 판정 체크. 반환으로는 판정 enum class 값을 돌려줌
    JUDGE_VECTOR_IDX JudgeCheck(float _TapTime);

    // 매 틱마다 키 입력을 체크 후 저장
    void KeyCheck(GEARLINE_TYPE _line, KEY _key);

    // 판정 시 해야 할 작업 (판정 벡터에 판정 기록, 판정 텍스트 이미지 애니메이션, Fever와 Combo 증가)
    void JudgementOperation(JUDGE_VECTOR_IDX _Judge, CNote* CurNote);

public: // 생성자, 소멸자
    CGear_PlayLevel(vector<int>* _vecJudge, CJudgeTexture* _JudgeTexture, CLineShine* _LineTexture, CCoolbomb* _CoolbombTexture, CCombo* _Combo, CFever* _Fever);
    ~CGear_PlayLevel();

    friend class CPlayLevel;
    friend class CGear_PlayLevel;
};

