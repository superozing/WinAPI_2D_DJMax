#pragma once
#include "CObj.h"

class CMusicDifficult :
    public CObj
{
private:
    // �⺻ ���̵� �ؽ���
    CTexture* m_Normal_DifficultBG;
    CTexture* m_Normal_Difficult;

    // SC ���̵� �ؽ���
    CTexture* m_SC_DifficultBG;
    CTexture* m_SC_Difficult;

    // ����: sc     ���̵�
    // ���: normal ���̵�
    int m_iCulDifficult;

private:
    virtual void tick(float _DT) override;
    virtual void render(HDC _dc) override;

public:
    void SetDifficult(int _difficult);

};

