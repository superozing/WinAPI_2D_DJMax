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

    bool m_isSC;

    BLENDFUNCTION m_blend;

private:
    virtual void render(HDC _dc) override;

public:
    void SetDifficult(int _difficult);
    int GetDifficult() const
    {
        if (m_isSC)
            return m_iCulDifficult * -1;
        return m_iCulDifficult;
    }

public:
    CLONE_DISABLE(CMusicDifficult);
    CMusicDifficult();
    CMusicDifficult(const CMusicDifficult& _Origin) = delete;
    ~CMusicDifficult();

};

