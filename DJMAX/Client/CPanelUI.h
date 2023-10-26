#pragma once
#include "CUI.h"

class CTexture;

class CPanelUI :
    public CUI
{
    GENERATED_OBJECT(CUI);
private:
    Vec2        m_vLbtnDownPos;
    CTexture*   m_Panel;

public:
    virtual void tick(float _DT) override;
    virtual void render(HDC _dc) override;

public:
    virtual void LBtnDown(Vec2 _MousePos) override;

public:
    //CLONE(CPanelUI);
    CPanelUI();
    ~CPanelUI();
};

