#include "pch.h"
#include "CBGA.h"
#include "CEngine.h"

HBITMAP VideoFrameProcessor::CreateHBITMAPFromSample(IMFSample* pSample, int videoWidth, int videoHeight)
{
    IMFMediaBuffer* pBuffer = nullptr;
    BYTE* pFrameData = nullptr;
    DWORD dwFrameLength = 0;
    if (pSample == nullptr)
        return nullptr;
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

void CBGA::tick(float _DT)
{
    static float acc = 0.f;

    acc += _DT;

    if (acc > float(1 / 24))
    {
        m_VideoFrameProcessor.ProcessVideoFrames();
        acc = 0.f;
    }
}

void CBGA::render(HDC _dc)
{
    TransparentBlt(_dc
                      , 0, 0
                      , 1600, 900
                      , m_hdc
                      , 0, 0
                      , 1600, 900
                      , RGB(0,0,1));
}

CBGA::CBGA(const wchar_t* _filepathname)
    :m_VideoFrameProcessor(_filepathname)
{
    m_hdc = CreateCompatibleDC(CEngine::GetInst()->GetMainDC());
    DeleteObject(SelectObject(m_hdc, m_VideoFrameProcessor.GetCurrentFrameBitmap()));
}

CBGA::~CBGA()
{
}
