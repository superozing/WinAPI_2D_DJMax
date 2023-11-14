#pragma once
#include "CObj.h"

class CCombo;

class CFever :
    public CObj
{
private:
    int m_CurFeverPower; // 현재 fever 배율

    int m_CurFeverGauge; // 현재 fever 게이지 충전량
    
private:
    // 틱, 렌더

    virtual void tick(float _DT) override;
    virtual void render(HDC _dc) override;

    // 비공개 멤버 함수

    void FeverPowerUp();
    void FeverBreak();



public:

    void FeverGaugeUp(JUDGE_VECTOR_IDX _judge);

    // get, set 함수

    int GetFeverPower() { return m_CurFeverGauge; }

public:
    CFever();
    ~CFever();

    friend class CCombo;
};

