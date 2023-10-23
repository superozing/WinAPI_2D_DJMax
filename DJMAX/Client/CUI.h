#pragma once
#include "CObj.h"

class CUI :
    public CObj
{
    GENERATED_OBJECT(CObj);

private:
    // ��� ���迡�� �θ� UI
    CUI*                m_ParentUI;

    // �ڽ��� ������ �ڽ� UI��
    vector<CUI*>        m_vecChildUI;
    
    // UI���� �θ��� ���� ��ġ�� ������� �߰����� pos�� ����.
    // �ֻ��� UI�� ��� ȭ�� ���� ��ġ, �Ҽӵ� UI�� ��� offset�� ��Ÿ��
    Vec2                m_vFinalPos;

    // ���콺�� UI ���� �÷��� �ִ°�
    bool                m_bMouseOn;
    // ���� �����ӿ��� ���콺�� �÷��� �־��°�
    bool                m_bMouseOn_Prev;
    // ���콺 �� �� ��ư�� ���ȴ°�
    bool                m_bMouseLBtnDown;

public:
    void AddChildUI(CUI* _ChildUI)
    {
        m_vecChildUI.push_back(_ChildUI);
        _ChildUI->m_ParentUI = this;
    }

public:
    virtual void tick(float _DT) override;
    virtual void render(HDC _dc) override;


    // �ڽ� �ʿ��� �ʿ��ϸ� ������ �� ���
    virtual void OnHovered(Vec2 _vMousePos) {}
    virtual void MouseOn(Vec2 _vMousePos) {}
    virtual void OnUnHovered(Vec2 _vMousePos) {}

    virtual void LBtnDown(Vec2 _vMousePos) {}
    virtual void LBtnUp(Vec2 _vMousePos) {}
    virtual void LBtnClicked(Vec2 _vMousePos) {}


public:
    Vec2 GetFinalPos() { return m_vFinalPos; }
    bool IsLBtnDown() { return m_bMouseLBtnDown; }

public:
    virtual CUI* Clone() = 0;
    CUI();
    CUI(const CUI& _Origin);
    ~CUI();

    friend class CUIMgr;
};

