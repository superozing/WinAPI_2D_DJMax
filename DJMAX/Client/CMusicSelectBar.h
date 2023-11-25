#pragma once
#include "CObj.h"

class CFocusUI;
class CMusicInfo;

class CMusicSelectBar :
    public CObj
{
private:
    const MUSICINFO&    m_MusicInfo;

    CTexture*           m_AlbumTexture;
    CFocusUI*           m_FocusUI;
    bool                m_isFocus;

    BLENDFUNCTION       blend;
    float alpha;
    CMusicInfo*         m_pOwnerInfo;
    int index;
public:
    virtual void tick(float _DT) override;
    virtual void render(HDC _dc) override;

    void SetFocus() { m_isFocus = true; }
    void SetUnFocus() { m_isFocus = false; }

    bool GetIsFocus() const { return m_isFocus; }
    int GetInfoIndex() const { return index; }
    CFocusUI* GetFocusUI() { return m_FocusUI; }
    BLENDFUNCTION GetBlendFunction() const { return blend; }
public:
    CLONE(CMusicSelectBar);
    CMusicSelectBar(MUSICINFO& _MusicInfo, CFocusUI* _FocusUI, Vec2 vPos, int _index, CMusicInfo* _pOwnerMusicInfo);
    ~CMusicSelectBar();

};

