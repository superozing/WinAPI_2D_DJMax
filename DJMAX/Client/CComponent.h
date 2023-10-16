#pragma once
#include "CEntity.h"

class CObj;

class CComponent :
    public CEntity
{
private:
    CObj* const m_pOwner; // ¼ÒÀ¯ÀÚ

public:
    CObj* GetOwner() { return m_pOwner; }

public:
    virtual void tick(float _DT) {}
    virtual void finaltick(float _DT) = 0;
    virtual void render(HDC _dc) {}

public:
    CComponent(CObj* _Owner);
    ~CComponent();
};

