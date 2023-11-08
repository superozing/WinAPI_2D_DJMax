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


CBGA::CBGA(const wchar_t* videoFilePath)
    : m_VideoFrameProcessor(videoFilePath), m_hBitmap(nullptr),
    frameProcessingInterval(1.0f / 24.0f), frameProcessingTime(0.0f) {
    // 비트맵 초기화
    InitializeBitmap();
}

CBGA::~CBGA() {
    // 비트맵 해제
    ReleaseBitmap();
}

void CBGA::tick(float _DT) {
    // 타이머를 사용하여 프레임 처리 간격을 조절
    frameProcessingTime += _DT;
    if (frameProcessingTime >= frameProcessingInterval) {
        m_VideoFrameProcessor.ProcessNextFrame();
        frameProcessingTime = 0.0f;
    }
}

void CBGA::render(HDC _dc) {
    // 비트맵 그리기
    if (m_hBitmap) {
        HDC hdcBitmap = CreateCompatibleDC(_dc);
        HBITMAP hOldBitmap = (HBITMAP)SelectObject(hdcBitmap, m_hBitmap);
        BitBlt(_dc, 0, 0, 1600, 900, hdcBitmap, 0, 0, SRCCOPY);
        SelectObject(hdcBitmap, hOldBitmap);
        DeleteDC(hdcBitmap);
    }
}

void CBGA::InitializeBitmap() {
    m_hBitmap = m_VideoFrameProcessor.GetCurrentFrameBitmap();
}

void CBGA::ReleaseBitmap() {
    if (m_hBitmap) {
        DeleteObject(m_hBitmap);
        m_hBitmap = nullptr;
    }
}