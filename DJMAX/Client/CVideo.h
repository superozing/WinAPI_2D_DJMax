#pragma once
#include "CComponent.h"

// 1. 이 컴포넌트는 애니메이터와 다르게 비디오 파일을 가져와 추출함.
// 2.

typedef struct _VMR9AlphaBitmap {
    DWORD dwFlags;
    HDC hdc;
    RECT rSrc;
    RECT rDst;
    FLOAT fAlpha;
    COLORREF clrSrcKey;
} VMR9AlphaBitmap;
class CVideo :
    public CComponent
{
private: 
    IGraphBuilder*  m_pGraph;
    IMediaControl*  m_pControl;
    IMediaEventEx*  m_pEvent;
    IBaseFilter*    m_pSource;
    IMediaSeeking*  m_pSeeking;
    IVideoWindow*   m_pVidWindow;

    IVMRWindowlessControl* pWindowlessControl = nullptr;
    VMR9AlphaBitmap bitmap;

    LONGLONG        m_duration;
    float           m_fFrame;
    HBITMAP         m_hBitmap;
public:
    virtual void finaltick(float _DT) override;
    virtual void render(HDC _dc) override;

    void AddSourceFilter(wstring _strFilePath, float _VidFrame);
public:
    CLONE(CVideo);
    CVideo(CObj* _Owner);
    CVideo(const CVideo& _Origin);
    ~CVideo();
};

