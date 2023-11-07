#pragma once
#include "CBackground.h"

template <class Interface>
void SafeRelease(Interface** ppInterfaceToRelease) {
    if (*ppInterfaceToRelease != nullptr) {
        (*ppInterfaceToRelease)->Release();
        *ppInterfaceToRelease = nullptr;
    }
}
IMFSourceReader* pReader = nullptr;
class VideoFrameProcessor 
{
public:
    VideoFrameProcessor(const wchar_t* videoFilePath) : videoFilePath(videoFilePath) {
        HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
        if (SUCCEEDED(hr)) {
            hr = MFCreateSourceReaderFromURL(videoFilePath, nullptr, &pReader);
        }

    }

    HRESULT ProcessVideoFrames() 
    {
        HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
        if (SUCCEEDED(hr)) 
        {
            IMFSourceReader* pReader = nullptr;
            hr = MFCreateSourceReaderFromURL(videoFilePath, nullptr, &pReader);

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
                        while (ProcessNextFrame(pReader)) 
                        {
                            // Frame processing completed
                        }
                    }

                    pMediaType->Release();
                }

                pReader->Release();
            }

            CoUninitialize();
        }

        return hr;
    }

private:
    const wchar_t* videoFilePath;

    bool ProcessNextFrame(IMFSourceReader* pReader) {
        IMFSample* pSample = nullptr;
        DWORD dwStreamFlags = 0;
        LONGLONG llTimestamp = 0;

        HRESULT hr = pReader->ReadSample(0, 0, nullptr, &dwStreamFlags, &llTimestamp, &pSample);

        if (FAILED(hr) || dwStreamFlags & MF_SOURCE_READERF_ENDOFSTREAM) {
            return false;
        }

        if (SUCCEEDED(hr) && pSample) {
            ProcessFrame(pSample);
        }

        return true;
    }

    void ProcessFrame(IMFSample* pSample) {
        // Process the frame here
        SaveFrameAsImage(pSample);
    }

    void SaveFrameAsImage(IMFSample* pSample) {
        IMFMediaBuffer* pBuffer = nullptr;
        BYTE* pFrameData = nullptr;
        DWORD dwFrameLength = 0;

        HRESULT hr = pSample->ConvertToContiguousBuffer(&pBuffer);
        if (SUCCEEDED(hr)) {
            hr = pBuffer->Lock(&pFrameData, nullptr, &dwFrameLength);
        }

        if (SUCCEEDED(hr)) {
            // Create an HBITMAP and save it as an image (similar to the previous code)
            // ...

            pBuffer->Unlock();
        }

        SafeRelease<IMFMediaBuffer>(&pBuffer);
    }

public:
    HBITMAP NextFrameBitmap();
};


class CBGA :
    public CBackground
{
public:
    VideoFrameProcessor m_frameBitmapData;
    HBITMAP             m_renderHBITMAP;

    virtual void tick(float _DT) override;
    virtual void render(HDC _dc) override;
public:
    CLONE_DISABLE(CBGA);
    CBGA(const wchar_t* _filepathname);
    CBGA(const CBGA& _Origin) = delete;
    ~CBGA();
};

