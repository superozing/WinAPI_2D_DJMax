#pragma once
#include "CObj.h"

// 문자를 관리할 때 이 걸 사용하면 편리하겠지?
// 크기 조절과 입력 될 숫자를 넘겨주면 render할 떄 자동으로 숫자에 맞는 이미지를 출력할 수 있도록 해주면 될 듯.

class CNumTexture :
    public CObj
{
private:
    int     m_FontSize;
    float   m_RealNumber;
    bool    m_isRealNumber;

private:
    virtual void tick(float _DT) override;
    virtual void render(HDC _dc) override;

public:
    void SetRealNum(float _RealNum) 
    {
        m_RealNumber = _RealNum; 
        m_isRealNumber = true;
    }
    void SetIntNum(int _IntegerNum) 
    { 
        m_RealNumber = _IntegerNum; 
        m_isRealNumber = false;
    }

    void SetFontSize(int _FontSize) { m_FontSize = _FontSize; }

public:
    CLONE(CNumTexture);
    CNumTexture();
    CNumTexture(const CNumTexture& _Origin);
    ~CNumTexture();
};

