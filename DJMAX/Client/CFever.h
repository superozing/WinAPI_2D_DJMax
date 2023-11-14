#pragma once
#include "CObj.h"

class CCombo;

class CFever :
    public CObj
{
private:
    int m_CurFeverPower; // ���� fever ����

    int m_CurFeverGauge; // ���� fever ������ ������
    
private:
    // ƽ, ����

    virtual void tick(float _DT) override;
    virtual void render(HDC _dc) override;

    // ����� ��� �Լ�

    void FeverPowerUp();
    void FeverBreak();



public:

    void FeverGaugeUp(JUDGE_VECTOR_IDX _judge);

    // get, set �Լ�

    int GetFeverPower() { return m_CurFeverGauge; }

public:
    CFever();
    ~CFever();

    friend class CCombo;
};

