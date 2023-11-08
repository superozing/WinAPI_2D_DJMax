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
    void DeleteNote();  // �ε����� ����Ű�� ���� ��Ʈ ����
    void EditNote();    // �ε����� ����Ű�� ���� ��Ʈ ���� (DialogBox()ȣ��)

    void SaveNoteData();

    CGear_EditorLevel();
    ~CGear_EditorLevel();
};
