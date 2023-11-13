#pragma once
#include "CObj.h"

// ���� ����
class CAnimator;


class CCoolbomb :
    public CObj
{
private:
    CAnimator* m_CoolbombAnimArr[4];

public:
    virtual void tick(float _DT) override;
    virtual void render(HDC _dc) override;

    void SetCoolbombAnimation(GEARLINE_TYPE _line, bool _isMaxJudge);
public:
    CLONE_DISABLE(CCoolbomb);
    CCoolbomb();
    CCoolbomb(const CCoolbomb& _Origin) = delete;
    ~CCoolbomb();
};

