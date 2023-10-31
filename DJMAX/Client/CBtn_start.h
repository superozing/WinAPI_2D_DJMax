#pragma once
#include "CBtnUI.h"

class CBtn_start :
    public CBtnUI
{
    GENERATED_OBJECT(CBtnUI);
    float m_fMoveUp;
public:
    void SelectPhase() { m_fMoveUp = 3000.f; }
    virtual void tick(float _DT) override;

public:
    CLONE(CBtn_start);
    CBtn_start();
    ~CBtn_start();

};

