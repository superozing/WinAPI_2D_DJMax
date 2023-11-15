#pragma once
#include "CObj.h"

class CFever;

class CCombo :
    public CObj
{
private:
    int         m_CurCombo;
    int         m_BestCombo;
    CFever*     m_FeverPower;

    // ��... �����ϸ� �Ʒ����� ���� �ڿ������� �ö���� ������ �ʿ��ѵ�
    // ��� �ϴ� ���� �������.....?

private:
    virtual void tick(float _DT) override;
    virtual void render(HDC _dc) override;

    void ComboBreak(); // �޺� �ʱ�ȭ (break ���� ��)

public:
    void ComboUp(JUDGE_VECTOR_IDX _judge); // �޺� ���� (break ���� �̿��� ��� ����)


public:
    void SetFeverPointer(CFever* _FeverPower) { m_FeverPower = _FeverPower; }


public:
    CLONE_DISABLE(CCombo);
    CCombo();
    CCombo(const CCombo& _Origin) = delete;
    ~CCombo();

//////
    friend class CFever;
};

