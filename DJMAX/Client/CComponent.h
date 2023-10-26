#pragma once
#include "CEntity.h"

class CObj;

class CComponent :
    public CEntity
{
private:
    CObj* m_pOwner; // ������

public:
    CObj* GetOwner() { return m_pOwner; }

public:
    virtual void tick(float _DT) {}
    virtual void finaltick(float _DT) = 0;
    virtual void render(HDC _dc) {}

public:
    virtual CComponent* Clone() = 0;    
    // Clone(���� ������)�� ������� �ʴ� ���������Լ��� ���ǵ� �θ� �ʿ��� ���� �����Լ��� �����ؾ� �ϴ� ����:
    // ���� ���Ѵٸ� Entity�����ͷ� ��ȯ�� ��, �� �۵��ϴµ�
    // �� �� ���� ������Ʈ ��ü�� �����ϰ� Clone���� ���� �� ���� Component��� �� �� �� ���̳��� ĳ��Ʈ�� ����ؾ� ��

public:
    CComponent(CObj* _Owner);
    ~CComponent();

    friend class CObj;
};

