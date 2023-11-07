#include "pch.h"
#include "CBGA.h"

HBITMAP CreateHBITMAPFromSample(IMFSample* pSample, int videoWidth, int videoHeight) 
{
    IMFMediaBuffer* pBuffer = nullptr;
    BYTE* pFrameData = nullptr;
    DWORD dwFrameLength = 0;

    HRESULT hr = pSample->ConvertToContiguousBuffer(&pBuffer);
    if (FAILED(hr)) {
        return nullptr;
    }

    hr = pBuffer->Lock(&pFrameData, nullptr, &dwFrameLength);
    if (FAILED(hr)) {
        SafeRelease(&pBuffer);
        return nullptr;
    }

    BITMAPINFOHEADER bi = { 0 };
    bi.biSize = sizeof(BITMAPINFOHEADER);
    bi.biWidth = videoWidth;
    bi.biHeight = -videoHeight;
    bi.biPlanes = 1;
    bi.biBitCount = 32;
    bi.biCompression = BI_RGB;

    HBITMAP hBitmap = CreateDIBitmap(GetDC(nullptr), &bi, CBM_INIT, pFrameData, (BITMAPINFO*)&bi, DIB_RGB_COLORS);

    pBuffer->Unlock();
    SafeRelease(&pBuffer);

    return hBitmap;
}

HBITMAP VideoFrameProcessor::NextFrameBitmap() 
{
    IMFSample* pSample = nullptr;
    DWORD dwStreamFlags = 0;
    LONGLONG llTimestamp = 0;

    HRESULT hr = pReader->ReadSample(0, 0, nullptr, &dwStreamFlags, &llTimestamp, &pSample);

    if (FAILED(hr) || dwStreamFlags & MF_SOURCE_READERF_ENDOFSTREAM) {
        return nullptr;
    }

    if (SUCCEEDED(hr) && pSample) {
        HBITMAP hBitmap = CreateHBITMAPFromSample(pSample, 1280, 720);
        SafeRelease(&pSample);
        return hBitmap;
    }

    return nullptr;
}

void CBGA::tick(float _DT)
{
}

void CBGA::render(HDC _dc)
{
    TransparentBlt(_dc, 0
                      , 0
                      , 1600, 900
                      , m_renderHBITMAP
                      , int(frm.vLeftTop.x), int(frm.vLeftTop.y)
                      , int(frm.vCutSize.x), int(frm.vCutSize.y)
                      , RGB(255, 0, 255));
}

CBGA::CBGA(const wchar_t* _filepathname)
    :m_frameBitmapData(_filepathname)
{
    m_renderHBITMAP = m_frameBitmapData.NextFrameBitmap();
}

CBGA::~CBGA()
{
}
