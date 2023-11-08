#pragma once
#include "CGear.h"

class CGear_EditorLevel;

struct NoteSec
{
    float			tap;
    float			release;

public:
    float NoteTimeDiff() { return release - tap; }
    void AddNoteSec(GEARLINE_TYPE _line, CGear_EditorLevel* _owner);

};
class CGear_EditorLevel :
    public CGear
{
public:
    CTexture*       m_FocusCogwheelTexture;
public:
    NoteSec			m_noteSecBufArr[(ULONGLONG)GEARLINE_TYPE::END];
    int				m_FocusIdx;

public: // level
    CEditorLevel* m_pOwner;
private:
    virtual void tick(float _DT) override;
    virtual void render(HDC _dc) override;

public:
    void AddNote(NOTE_TYPE _type, float _tapTime, float _pressTime, GEARLINE_TYPE _line);
    void DeleteNote();  // 인덱스가 가리키는 현재 노트 삭제
    void EditNote();    // 인덱스가 가리키는 현재 노트 수정 (DialogBox()호출)

    void SaveNoteData();

    CGear_EditorLevel();
    ~CGear_EditorLevel();
};

