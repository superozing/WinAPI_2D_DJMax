#pragma once
#include "CObj.h"

class CTexture;

class CStringTexture :
    public CObj
{
private:
    CTexture* m_strTexture;

    BLENDFUNCTION m_blend;
private:

    virtual void render(HDC _dc) override;

public:
    void SetTexture(CTexture* _texture) { m_strTexture = _texture; }
    void SetAlpha(BYTE _alpha) { m_blend.SourceConstantAlpha = _alpha; }

    CTexture* GetTexture() { return m_strTexture; }
public:
    CLONE(CStringTexture);
    CStringTexture();
    CStringTexture(const CStringTexture& _Origin);
    ~CStringTexture();


    friend class CMusicInfo;
};

