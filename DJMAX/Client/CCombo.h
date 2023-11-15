#pragma once
#include "CObj.h"

class CFever;

class CCombo :
    public CObj
{
private:
    int         m_CurCombo;
    int         m_BestCombo;
    CFever*     m_FeverPower;

    // 음... 판정하면 아래에서 위로 자연스럽게 올라오는 연출이 필요한데
    // 어떻게 하는 것이 좋을까요.....?

private:
    virtual void tick(float _DT) override;
    virtual void render(HDC _dc) override;

    void ComboBreak(); // 콤보 초기화 (break 판정 시)

public:
    void ComboUp(JUDGE_VECTOR_IDX _judge); // 콤보 증가 (break 판정 이외의 모든 판정)


public:
    void SetFeverPointer(CFever* _FeverPower) { m_FeverPower = _FeverPower; }


public:
    CLONE_DISABLE(CCombo);
    CCombo();
    CCombo(const CCombo& _Origin) = delete;
    ~CCombo();

//////
    friend class CFever;
};

