#pragma once
#include "CUI.h"

class CTexture;

// typedef로 마치 자료형 처럼 사용 가능하도록 만들기.
typedef  void(*BtnCallBack)(void);
typedef  void(CEntity::* DelegateFunc)(void);



class CBtnUI :
    public CUI
{
    GENERATED_OBJECT(CUI);
private: // 현재 호출된 함수에 따라서 다르게 보여질 텍스처 들
    
    // 기본
    CTexture* m_NormalImg; 
    // 마우스가 올라옴
    CTexture* m_HoverImg;
    // 마우스가 눌림
    CTexture* m_PressedImg;

    // 위의 3개의 이미지 중 현재 출력할 이미지를 가리킬 멤버.
    CTexture* m_CurImg;

private: // Callback 방식과 Delegate 방식 모두 사용 가능.
    // 콜백 (전역함수 포인터) 
    BtnCallBack m_CallBackFunc;

    // 델리게이트(맴버함수 포인터, 객체)
    // 객체의 주소
    CEntity* m_Inst;
    // 맴버함수의 주소
    DelegateFunc    m_Delegate;

    BLENDFUNCTION blend;

public:
    void SetNormalImg(CTexture* _NormalImg) { m_NormalImg = _NormalImg; }
    void SetPressedImg(CTexture* _PressedImg) { m_PressedImg = _PressedImg; }
    void SetHoverImg(CTexture* _HoverImg) { m_HoverImg = _HoverImg; }
    void SetCallBack(BtnCallBack _CallBack) { m_CallBackFunc = _CallBack; }
    void SetDeletage(CEntity* _Inst, DelegateFunc _Func) { m_Inst = _Inst; m_Delegate = _Func; }

public:
    virtual void tick(float _DT) override;
    virtual void render(HDC _dc) override;

public:
    // 마우스가 버튼 위로 올라옴
    virtual void OnHovered(Vec2 _vMousePos) override;
    // 마우스가 버튼 위에서 벗어남
    virtual void OnUnHovered(Vec2 _vMousePos) override;
    // 마우스가 버튼 위에 올라와 있는 상태임
    virtual void MouseOn(Vec2 _vMousePos) override;

    // 마우스 왼 쪽이 눌림
    virtual void LBtnDown(Vec2 _vMousePos) override;
    // 마우스 왼 쪽이 떼어짐
    virtual void LBtnUp(Vec2 _vMousePos) override;

    // - 클릭 상태 - 마우스의 왼 쪽이 버튼 위에 올라와 있는 상태에서 떼어짐 
    virtual void LBtnClicked(Vec2 _vMousePos) override;


public:
    CLONE(CBtnUI);
    CBtnUI();
    ~CBtnUI();
};

