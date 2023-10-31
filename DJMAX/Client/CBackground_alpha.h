#pragma once
#include "CBackground.h"

class CBackground_alpha :
    public CBackground
{
private:
    float m_acc;
    virtual void tick(float _DT) override;

public:
    CBackground_alpha();
    ~CBackground_alpha();
};

