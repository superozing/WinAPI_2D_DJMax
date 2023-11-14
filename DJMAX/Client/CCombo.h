#pragma once
#include "CObj.h"

class CFever;

class CCombo :
    public CObj
{
private:
    int m_CurCombo;
    int m_BestCombo;
    CFever* m_FeverPower;
private:
    virtual void tick(float _DT) override;
    virtual void render(HDC _dc) override;

public:
    void ComboUp();
    void ComboBreak();

//////
    friend class CFever;
};

