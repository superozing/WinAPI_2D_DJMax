#pragma once
#include "CComponent.h"

// 1. �� ������Ʈ�� �ִϸ����Ϳ� �ٸ��� ���� ������ ������ ������.
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

