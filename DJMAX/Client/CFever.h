#pragma once
#include "CObj.h"

class CCombo;
class CSound;


class CFever :
    public CObj
{
private:
    int m_CurFeverPower; // 현재 fever 배율
    int m_CurFeverGauge; // 현재 fever 게이지 충전량

    // 1. 기어 백그라운드
    CTexture*   m_FeverGearBG;
    CTexture*   m_FeverGearText;

    // 2. 배율 텍스트 아틀라스 y250
    CTexture* m_FeverTextAtlas;
    float m_FeverTextSizePercent;

    // 3. 게이지 바, 196 x 8 y400
    CTexture* m_FeverBarAtlas;
    CTexture* m_FeverBarBG;


    // 4. 링 아틀라스
    CTexture*   m_FeverRingAtlas;
    float         m_FeverTriggerPercent;

    // 효과음
    CSound*     m_FeverEffectSound;

private:
    // 틱, 렌더

    virtual void tick(float _DT) override;
    virtual void render(HDC _dc) override;

    // 비공개 멤버 함수

    void FeverPowerUp();
    void FeverBreak();



public:
    void GearInsideRender(HDC _dc);

    void FeverGaugeUp(JUDGE_VECTOR_IDX _judge);

    // get, set 함수

    int GetFeverPower() { return m_CurFeverPower; }

public:
    CLONE_DISABLE(CFever);
    CFever();
    CFever(const CFever& _Origin) = delete;
    ~CFever();

    friend class CCombo;
};

