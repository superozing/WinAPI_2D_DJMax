#pragma once
#include "CObj.h"

// ���ڸ� ������ �� �� �� ����ϸ� ���ϰ���?
// ũ�� ������ �Է� �� ���ڸ� �Ѱ��ָ� render�� �� �ڵ����� ���ڿ� �´� �̹����� ����� �� �ֵ��� ���ָ� �� ��.

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

