#pragma once
#include "CObj.h"
#include "components.h"

class CLevelChoice
	: public CObj
{
    GENERATED_OBJECT(CObj);
private:
    CTexture*       m_NormalImg;
    CAnimator*      m_HoverAnimator;
    
    // 둘 중 어느 것을 실행 할 지.
    bool            m_isAnim;

public:
    void SetNormalImg(CTexture* _NormalImg) { m_NormalImg = _NormalImg; }
    void SetHoverAnim(CAnimator* _HoverImg) { m_HoverAnimator = _HoverImg; }
public:
    virtual void tick(float _DT) override;
    virtual void render(HDC _dc) override;
public:
    virtual void OnHovered(Vec2 _vMousePos);
    virtual void OnUnHovered(Vec2 _vMousePos);
public:
    CLONE(CLevelChoice);
    CLevelChoice();
    ~CLevelChoice();

    friend class CStartLevel;
};

