#pragma once
#include "CBtnUI.h"

class CMusicSelectBar;

class CFocusUI :
    public CBtnUI
{
private:
    CMusicSelectBar* m_pOwnerBar;
    class CMusicInfo*      m_pOwnerInfo;

    virtual void LBtnClicked(Vec2 _vMousePos) override;

public:
    virtual void render(HDC _dc) override;
    void SetOwnerBar(CMusicSelectBar* _pOwnerBar) { m_pOwnerBar = _pOwnerBar; }
    
public:
    CLONE(CFocusUI);
    CFocusUI(class CMusicInfo* _pOwnerInfo);
    CFocusUI(const CFocusUI& _Origin);
    ~CFocusUI();
};

