#pragma once
#include "CObj.h"

class CTexture;
class CGear_PlayLevel;

struct ShineTex
{
    bool        isRender;
    BYTE        alpha;
    CTexture*   pShineTex;
};

class CLineShine :
    public CObj
{
private:
    ShineTex* m_LineTex[4];
    ShineTex* m_ButtonTex[4];


    CGear_PlayLevel* m_pOwnerGear;
private:
    virtual void render(HDC _dc) override;
public:
    void SetShineOn(GEARLINE_TYPE _ShineLine);
    void SetShineOff(GEARLINE_TYPE _ShineLine);

public:
    // 위치 정보를 알기 위해서 기어를 들고 있어야 한다.
    void SetOwnerGear(CGear_PlayLevel* _pOwnerGear) { m_pOwnerGear = _pOwnerGear; }

public:
    CLONE_DISABLE(CLineShine);
    CLineShine();
    ~CLineShine();
    friend class CGear_PlayLevel;
};

