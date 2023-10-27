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
    // ��� ��Ʈ�ʰ� �̹��� DC ����
    DeleteObject(m_hBit);
    DeleteDC(m_hDC);
}


bool CTexture::Load(const wstring& _strFilePath)
{
	wchar_t szExt[20] = {};

	// Ȯ���� ��������
	_wsplitpath_s(_strFilePath.c_str(), nullptr, 0, nullptr, 0, nullptr, 0, szExt, 20);

	// �о�� ������ bmp�ΰ�?
	if (!wcscmp(szExt, L".bmp") || !wcscmp(szExt, L".BMP"))
	{
		// �÷��̾ ����� �̹��� ��Ʈ�� �ε�
		m_hBit = (HBITMAP)LoadImage(nullptr, _strFilePath.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		if (nullptr == m_hBit)
		{
			return false;
		}
	}
	
	// �о�� ������ png�ΰ�?
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
	// x y ���� �ָ� ũ�⿡ �´� ��Ʈ���� �����־��
	m_hBit = CreateCompatibleBitmap(CEngine::GetInst()->GetMainDC(), _Width, Height);
	// DC ����
	m_hDC = CreateCompatibleDC(CEngine::GetInst()->GetMainDC());

	// ���� 1x1 ��Ʈ�� ����鼭 �ش� DC�� �׸��׸� �� �ֵ��� select
	DeleteObject(SelectObject(m_hDC, m_hBit));
	GetObject(m_hBit, sizeof(BITMAP), &m_Info); // ��Ʈ��
}
