#pragma once
#include "CBackground.h"

template <class Interface>
void SafeRelease(Interface** ppInterfaceToRelease) 
{
    if (*ppInterfaceToRelease != nullptr) 
    {
        (*ppInterfaceToRelease)->Release();
        *ppInterfaceToRelease = nullptr;
    }
}

class VideoFrameProcessor 
{
private:
    const wchar_t*      videoFilePath;
    IMFSourceReader*    pReader;
    HBITMAP             hBitmap;
    IMFSample*          pSample; // IMFSample ��� ���� �߰�
    HRESULT hr;

public:
    HRESULT ProcessVideoFrames() 
    {
        // ��Ʈ�� ������ ���� ��Ʈ�� �ʱ�ȭ
        InitializeBitmap();

        if (SUCCEEDED(hr)) 
        {
            DWORD dwStreamIndex = 0;
            IMFMediaType* pMediaType = nullptr;

            hr = pReader->SetStreamSelection(dwStreamIndex, TRUE);

            if (SUCCEEDED(hr)) 
            {
                hr = pReader->GetCurrentMediaType(dwStreamIndex, &pMediaType);
            }

            if (SUCCEEDED(hr)) 
            {
                GUID majorType;
                hr = pMediaType->GetMajorType(&majorType);

                if (SUCCEEDED(hr) && majorType == MFMediaType_Video) 
                {
                    ProcessNextFrame(pReader);
                }

                pMediaType->Release();
            }
        }

        return hr;
    }
    HBITMAP CreateHBITMAPFromSample(IMFSample* pSample, int videoWidth, int videoHeight);
    HBITMAP GetCurrentFrameBitmap() 
    {
        return hBitmap;
    }

    void InitializeBitmap() 
    {
        // ��Ʈ�� ���� �� ���� (�� �κ��� ��Ʈ�� ���� �� ������ �ش��ϴ� �ڵ�� ��ü�ؾ� ��)
        hBitmap = CreateHBITMAPFromSample(pSample, 1280, 720);
    }

    bool ProcessNextFrame(IMFSourceReader* pReader) 
    {
        IMFSample* pSample = nullptr;
        DWORD dwStreamFlags = 0;
        LONGLONG llTimestamp = 0;

        HRESULT hr = pReader->ReadSample(0, 0, nullptr, &dwStreamFlags, &llTimestamp, &pSample);

        if (FAILED(hr) || dwStreamFlags & MF_SOURCE_READERF_ENDOFSTREAM) 
        {
            return false;
        }

        if (SUCCEEDED(hr) && pSample)
        {
            // ������ ��Ʈ�� ������Ʈ
            UpdateBitmapFromSample(pSample);
        }

        return true;
    }

    void UpdateBitmapFromSample(IMFSample* pSample)
    {
        IMFMediaBuffer* pBuffer = nullptr;
        BYTE* pFrameData = nullptr;
        DWORD dwFrameLength = 0;

        HRESULT hr = pSample->ConvertToContiguousBuffer(&pBuffer);
        if (SUCCEEDED(hr)) 
        {
            hr = pBuffer->Lock(&pFrameData, nullptr, &dwFrameLength);
        }

        if (SUCCEEDED(hr)) 
        {
            // ��Ʈ�� ���� ������Ʈ (��: �޸� ����)
            // ...

            pBuffer->Unlock();
        }

        SafeRelease(&pBuffer);
    }

public:
    VideoFrameProcessor(const wchar_t* videoFilePath) 
        : videoFilePath(videoFilePath) 
    {
        hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
        if (SUCCEEDED(hr)) 
        {
            hr = MFCreateSourceReaderFromURL(videoFilePath, nullptr, &pReader);
        }

        // ��Ʈ�� ���� �� �ʱ�ȭ
        InitializeBitmap();
    }

    ~VideoFrameProcessor() 
    {
        SafeRelease(&pReader);

        // ��Ʈ�� ����
        DeleteObject(hBitmap);
    }


    friend class CBGA;
};

class CObj;

class CBGA
    : public CObj
{
private:
    VideoFrameProcessor m_VideoFrameProcessor;
    HDC                 m_hdc;
public:
    virtual void tick(float _DT) override;
    virtual void render(HDC _dc) override;
public:
    CLONE_DISABLE(CBGA);
    CBGA(const wchar_t* _filepathname);
    ~CBGA();
};