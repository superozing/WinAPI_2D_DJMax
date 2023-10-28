#include "pch.h"
#include "CVideo.h"

CVideo::CVideo(CObj* _Owner)
	:CComponent(_Owner)
	,m_pGraph(nullptr)
	,m_pControl(nullptr)
	,m_pEvent(nullptr)
	,m_pSource(nullptr)
	,m_pVidWindow(nullptr)
	,m_fFrame(0.f)
	, m_hBitmap(nullptr)
{
	CoInitialize(nullptr);
	CoCreateInstance(CLSID_FilterGraph, nullptr, CLSCTX_INPROC_SERVER, IID_IGraphBuilder, (void**)&m_pGraph);
	m_pGraph->QueryInterface(IID_IMediaControl, (void**)&m_pControl);
	m_pGraph->QueryInterface(IID_IMediaEventEx, (void**)&m_pEvent);
}

CVideo::CVideo(const CVideo& _Origin)
	:CComponent(_Origin)
	, m_pGraph(nullptr)
	, m_pControl(nullptr)
	, m_pEvent(nullptr)
	, m_pSource(nullptr)
	, m_pVidWindow(nullptr)

{
	CoInitialize(nullptr);
	CoCreateInstance(CLSID_FilterGraph, nullptr, CLSCTX_INPROC_SERVER, IID_IGraphBuilder, (void**)&m_pGraph);
	m_pGraph->QueryInterface(IID_IMediaControl, (void**)&m_pControl);
	m_pGraph->QueryInterface(IID_IMediaEventEx, (void**)&m_pEvent);
}

CVideo::~CVideo()
{
	m_pVidWindow->put_FullScreenMode(OAFALSE);
	m_pVidWindow->Release();
	m_pSource->Release();
	m_pEvent->Release();
	m_pControl->Release();
	m_pGraph->Release();
		m_pSeeking->Release(); // �������̽��� ����� �� �ݵ�� ����
	CoUninitialize();
	DeleteObject(m_hBitmap);
}

void CVideo::AddSourceFilter(wstring _strFilePath, float _VidFrame)
{
	m_pGraph->AddSourceFilter(_strFilePath.c_str(), L"Source Filter", &m_pSource);
	m_fFrame = _VidFrame;

	m_pGraph->QueryInterface(IID_IVideoWindow, (void**)&m_pVidWindow);
	m_pVidWindow->put_FullScreenMode(OATRUE);
	m_pControl->Run();
	m_pEvent->WaitForCompletion(INFINITE, nullptr);
}

void CVideo::finaltick(float _DT)
{
	if (SUCCEEDED(m_pGraph->QueryInterface(IID_IMediaSeeking, (void**)&m_pSeeking)))
	{
		LONGLONG currentPos, nextFramePos;
		m_pSeeking->GetCurrentPosition(&currentPos);
		m_pSeeking->GetDuration(&m_duration);

		// frameDuration�� ������ ���� �ð� �����Դϴ�.
		nextFramePos = currentPos + m_fFrame;

		// �� ���� �ȳѵ���
		if (nextFramePos > m_duration) 
		{
			nextFramePos = m_duration;
		}
		m_pSeeking->SetPositions(&nextFramePos, AM_SEEKING_AbsolutePositioning, nullptr, AM_SEEKING_NoPositioning);
	}

}

void CVideo::render(HDC _dc)
{
	pWindowlessControl->GetCurrentImage(&bitmap);
	if (SUCCEEDED()
	{

	}
	else {
		// ��Ʈ�� �����͸� �������� ���� ��� ó���� �۾��� ����
	}
}


