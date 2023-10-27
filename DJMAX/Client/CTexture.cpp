#include "pch.h"
#include "CTexture.h"

#include "CEngine.h"

CTexture::CTexture()
    :m_hBit(nullptr)
    ,m_hDC(nullptr)
    ,m_Info{}
{
}

CTexture::~CTexture()
{
    // 멤버 비트맵과 이미지 DC 해제
    DeleteObject(m_hBit);
    DeleteDC(m_hDC);
}


bool CTexture::Load(const wstring& _strFilePath)
{
	wchar_t szExt[20] = {};

	// 확장자 가져오기
	_wsplitpath_s(_strFilePath.c_str(), nullptr, 0, nullptr, 0, nullptr, 0, szExt, 20);

	// 읽어온 파일이 bmp인가?
	if (!wcscmp(szExt, L".bmp") || !wcscmp(szExt, L".BMP"))
	{
		// 플레이어가 사용할 이미지 비트맵 로딩
		m_hBit = (HBITMAP)LoadImage(nullptr, _strFilePath.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		if (nullptr == m_hBit)
		{
			return false;
		}
	}
	
	// 읽어온 파일이 png인가?
	else if (!wcscmp(szExt, L".png") || !wcscmp(szExt, L".PNG"))
	{
		ULONG_PTR gdiplusToken = 0;
		GdiplusStartupInput gidstartupInput = {};
		GdiplusStartup(&gdiplusToken, &gidstartupInput, nullptr);
		Image* pImg = Image::FromFile(_strFilePath.c_str(), false);

		Bitmap* pBitmap = (Bitmap*)pImg->Clone();
		Status stat = pBitmap->GetHBITMAP(Color(0, 0, 0, 0), &m_hBit);

		if (Status::Ok != stat)
			return false;
	}

	m_hDC = CreateCompatibleDC(CEngine::GetInst()->GetMainDC());
	DeleteObject(SelectObject(m_hDC, m_hBit));
	GetObject(m_hBit, sizeof(BITMAP), &m_Info);

	return true;
}

void CTexture::Create(UINT _Width, UINT Height)
{
	// x y 값을 주면 크기에 맞는 비트맵을 돌려주어요
	m_hBit = CreateCompatibleBitmap(CEngine::GetInst()->GetMainDC(), _Width, Height);
	// DC 연결
	m_hDC = CreateCompatibleDC(CEngine::GetInst()->GetMainDC());

	// 기존 1x1 비트맵 지우면서 해당 DC에 그림그릴 수 있도록 select
	DeleteObject(SelectObject(m_hDC, m_hBit));
	GetObject(m_hBit, sizeof(BITMAP), &m_Info); // 비트맵
}
