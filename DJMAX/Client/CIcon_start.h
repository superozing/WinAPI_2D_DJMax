#pragma once
#include "CIcon.h"

class CIcon_start :
    public CIcon
{
    GENERATED_OBJECT(CIcon);
private:
    float   m_fMoveUp;
public:
    void SelectPhase() { m_fMoveUp = 3000.f; }
    virtual void tick(float _DT) override;


public:
    CLONE(CIcon_start);
    CIcon_start();
    ~CIcon_start();

};

