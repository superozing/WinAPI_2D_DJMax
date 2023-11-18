#pragma once
#include "CObj.h"

// ���ڸ� ������ �� �� �� ����ϸ� ���ϰ���?
// ũ�� ������ �Է� �� ���ڸ� �Ѱ��ָ� render�� �� �ڵ����� ���ڿ� �´� �̹����� ����� �� �ֵ��� ���ָ� �� ��.

class CNumTexture :
    public CObj
{
private:
    float           m_FontSize;
    float           m_RealNumber;
    bool            m_isRealNumber;

    vector<int>     m_NumOfDigits;

private: // �ؽ���
    CTexture*       m_NumAtlas;
    BLENDFUNCTION   m_blend;

private:
    virtual void render(HDC _dc) override;

    // �� ������ �Է� �� �ڸ� �� ���� ����
    void ResetVector();

public:
    void SetRealNum(float _RealNum) 
    {
        m_RealNumber = _RealNum; 
        m_isRealNumber = true;
        ResetVector();
    }
    void SetIntNum(int _IntegerNum) 
    { 
        m_RealNumber = _IntegerNum; 
        m_isRealNumber = false;
        ResetVector();
    }

    void SetFontSize(float _FontSize) { m_FontSize = _FontSize; }

public:
    CLONE(CNumTexture);
    CNumTexture();
    CNumTexture(float _FontSize);
    CNumTexture(const CNumTexture& _Origin);
    ~CNumTexture();
};

