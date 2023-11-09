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
    IMFSample*          pSample; // IMFSample 멤버 변수 추가
    HRESULT             hr;
    IMFAttributes* pAttributes;
public:
    HRESULT ProcessVideoFrames() 
    {
        // 비트맵 재사용을 위해 비트맵 초기화
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
        // 비트맵 생성 및 설정 (이 부분은 비트맵 생성 및 설정에 해당하는 코드로 대체해야 함)
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
            // 프레임 비트맵 업데이트
            UpdateBitmapFromSample(pSample);
        }
        else {
            // pSample이 유효하지 않을 때의 처리
            // 예를 들어, 오류 메시지를 출력하거나 다른 처리를 수행할 수 있음
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
            // 비트맵 내용 업데이트 (예: 메모리 복사)
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
            // 오류 처리: pReader 초기화 실패
            // 오류 메시지 출력
            MessageBox(nullptr, L"Failed to initialize pReader.", L"Error", MB_OK | MB_ICONERROR);
            
            pReader = nullptr; // pReader 초기화 실패 시 nullptr로 설정
        }

        // 비트맵 생성 및 초기화
        InitializeBitmap();
    }

    ~VideoFrameProcessor() 
    {
        // COM 초기화 정리
        CoUninitialize();

        SafeRelease(&pReader);

        // 비트맵 해제
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

    // 추가: 비디오 처리 간격 조절을 위한 타이머 변수
    float frameProcessingInterval;
    float frameProcessingTime;

    // 추가: 비트맵 초기화 및 해제 메서드
    void InitializeBitmap();
    void ReleaseBitmap();
};