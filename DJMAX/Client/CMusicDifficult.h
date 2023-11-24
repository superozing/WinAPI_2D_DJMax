#pragma once
#include "CObj.h"

class CMusicDifficult :
    public CObj
{
private:
    // 기본 난이도 텍스쳐
    CTexture* m_Normal_DifficultBG;
    CTexture* m_Normal_Difficult;

    // SC 난이도 텍스쳐
    CTexture* m_SC_DifficultBG;
    CTexture* m_SC_Difficult;

    // 음수: sc     난이도
    // 양수: normal 난이도
    int m_iCulDifficult;

private:
    virtual void tick(float _DT) override;
    virtual void render(HDC _dc) override;

public:
    void SetDifficult(int _difficult);

};

