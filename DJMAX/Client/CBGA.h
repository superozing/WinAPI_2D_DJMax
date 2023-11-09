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
    HRESULT             hr;
    IMFAttributes* pAttributes;
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
                    ProcessNextFrame();
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

    bool ProcessNextFrame() 
    {
        IMFSample* pSample = nullptr;
        DWORD dwStreamFlags = 0;
        LONGLONG llTimestamp = 0;

        HRESULT hr = pReader->ReadSample(0, 0, nullptr, &dwStreamFlags, &llTimestamp, &pSample);

        if (FAILED(hr) || dwStreamFlags & MF_SOURCE_READERF_ENDOFSTREAM) {
            return false;
        }

        if (SUCCEEDED(hr) && pSample) {
            // ������ ��Ʈ�� ������Ʈ
            UpdateBitmapFromSample(pSample);
        }
        else {
            // pSample�� ��ȿ���� ���� ���� ó��
            // ���� ���, ���� �޽����� ����ϰų� �ٸ� ó���� ������ �� ����
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
        , pReader(nullptr)
        , hBitmap(nullptr) 
        , pAttributes(nullptr)
    {
        hr = MFCreateAttributes(&pAttributes, 1);
        if (SUCCEEDED(hr))
        {
            hr = pAttributes->SetUINT32(MF_SOURCE_READER_ENABLE_VIDEO_PROCESSING, TRUE);
        }


        hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
        pReader = nullptr;
        if (SUCCEEDED(hr)) //videoFilePath
        {
            hr = MFCreateSourceReaderFromURL(L"C:\\01.WinAPI2D\\WinAPI_2D_DJMax\\DJMAX\\DJMAX\\content\\Video\\MICDROP.mp4", /*pAttributes*/nullptr , &pReader);
            int a = 1;
            a = 3;
        }

        if (FAILED(hr))
        {
            // ���� ó��: pReader �ʱ�ȭ ����
            // ���� �޽��� ���
            MessageBox(nullptr, L"Failed to initialize pReader.", L"Error", MB_OK | MB_ICONERROR);
            
            pReader = nullptr; // pReader �ʱ�ȭ ���� �� nullptr�� ����
        }

        // ��Ʈ�� ���� �� �ʱ�ȭ
        InitializeBitmap();
    }

    ~VideoFrameProcessor() 
    {
        // COM �ʱ�ȭ ����
        CoUninitialize();

        SafeRelease(&pReader);

        // ��Ʈ�� ����
        DeleteObject(hBitmap);
    }


    friend class CBGA;
};

class CObj;

class CBGA : public CObj {
public:
    CLONE_DISABLE(CBGA);
    CBGA(const wchar_t* videoFilePath);
    CBGA(const CBGA& _Origin) = delete;
    virtual ~CBGA();

    virtual void tick(float _DT) override;
    virtual void render(HDC _dc) override;

private:
    VideoFrameProcessor m_VideoFrameProcessor;
    HBITMAP m_hBitmap;

    // �߰�: ���� ó�� ���� ������ ���� Ÿ�̸� ����
    float frameProcessingInterval;
    float frameProcessingTime;

    // �߰�: ��Ʈ�� �ʱ�ȭ �� ���� �޼���
    void InitializeBitmap();
    void ReleaseBitmap();
};