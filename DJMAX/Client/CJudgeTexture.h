#pragma once
#include "CObj.h"

class CAnimator;

class CJudgeTexture :
    public CObj
{
private:
    CAnimator*   m_arrJudgeTexAnim;

    float       m_AnimTime;// 애니메이션 재생 초를 누적해서 체크.  
public:
    virtual void tick(float _DT) override;
    virtual void render(HDC _dc) override;

    void SetJudgeAnimation(JUDGE_VECTOR_IDX _JudgeIndex);
public:
    CLONE_DISABLE(CJudgeTexture);
    CJudgeTexture();
    CJudgeTexture(const CJudgeTexture& _Origin) = delete;
    ~CJudgeTexture();

};

