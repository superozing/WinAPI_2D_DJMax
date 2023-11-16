#pragma once
#include "CObj.h"

class CAnimator;
class CGear_PlayLevel;

class CJudgeTexture :
    public CObj
{
private:
    CAnimator*   m_arrJudgeTexAnim;

    CGear_PlayLevel* m_pOwnerGear;
public:
    virtual void tick(float _DT) override;
    virtual void render(HDC _dc) override;

    void SetJudgeAnimation(JUDGE_VECTOR_IDX _JudgeIndex);
    void SetOwnerGear(CGear_PlayLevel* _pOwnerGear) { m_pOwnerGear = _pOwnerGear; }
public:
    CLONE_DISABLE(CJudgeTexture);
    CJudgeTexture();
    CJudgeTexture(const CJudgeTexture& _Origin) = delete;
    ~CJudgeTexture();

};

