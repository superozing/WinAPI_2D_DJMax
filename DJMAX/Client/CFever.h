#pragma once
#include "CObj.h"

class CCombo;
class CSound;


class CFever :
    public CObj
{
private:
    int m_CurFeverPower; // ���� fever ����
    int m_CurFeverGauge; // ���� fever ������ ������

    // 1. ��� ��׶���
    CTexture*   m_FeverGearBG;
    CTexture*   m_FeverGearText;

    // 2. ���� �ؽ�Ʈ ��Ʋ�� y250
    CTexture* m_FeverTextAtlas;
    float m_FeverTextSizePercent;

    // 3. ������ ��, 196 x 8 y400
    CTexture* m_FeverBarAtlas;
    CTexture* m_FeverBarBG;


    // 4. �� ��Ʋ��
    CTexture*   m_FeverRingAtlas;
    float         m_FeverTriggerPercent;

    // ȿ����
    CSound*     m_FeverEffectSound;

private:
    // ƽ, ����

    virtual void tick(float _DT) override;
    virtual void render(HDC _dc) override;

    // ����� ��� �Լ�

    void FeverPowerUp();
    void FeverBreak();



public:
    void GearInsideRender(HDC _dc);

    void FeverGaugeUp(JUDGE_VECTOR_IDX _judge);

    // get, set �Լ�

    int GetFeverPower() { return m_CurFeverPower; }

public:
    CLONE_DISABLE(CFever);
    CFever();
    CFever(const CFever& _Origin) = delete;
    ~CFever();

    friend class CCombo;
};

