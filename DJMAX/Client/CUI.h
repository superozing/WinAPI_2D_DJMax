#pragma once
#include "CObj.h"

class CUI :
    public CObj
{
    GENERATED_OBJECT(CObj);

private:
    // 상속 관계에서 부모 UI
    CUI*                m_ParentUI;

    // 자신이 가지는 자식 UI들
    vector<CUI*>        m_vecChildUI;
    
    // UI들은 부모의 최종 위치를 기반으로 추가적임 pos를 더함.
    // 최상위 UI일 경우 화면 상의 위치, 소속된 UI일 경우 offset을 나타냄
    Vec2                m_vFinalPos;

    // 마우스가 UI 위에 올려져 있는가
    bool                m_bMouseOn;
    // 이전 프레임에도 마우스가 올려져 있었는가
    bool                m_bMouseOn_Prev;
    // 마우스 왼 쪽 버튼이 눌렸는가
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


public: // 자식 쪽에서 필요하면 재정의 후 사용
    
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

