#pragma once
#include "CObj.h"

class CPlayLevel;
class CBtnUI;

class CPause :
    public CObj
{
    CPlayLevel* m_pOwner;

    class  CStringTexture* m_PauseTxt;

    CBtnUI*     m_ContinueBtn;
    CBtnUI*     m_RestartBtn;
    CBtnUI*     m_ExitBtn;

private:
    void tick(float _DT) override;
    void render(HDC _dc) override;


public:
    CLONE_DISABLE(CPause);
    CPause(CPlayLevel* pOwnerLevel);
    CPause(const CPause& _Origin) = delete;
    ~CPause();
};

