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

    void PlayCoolbombAnimation(GEARLINE_TYPE _line, JUDGE_VECTOR_IDX _Judge);

public:
    CLONE_DISABLE(CCoolbomb);
    CCoolbomb();
    CCoolbomb(const CCoolbomb& _Origin) = delete;
    ~CCoolbomb();
};

