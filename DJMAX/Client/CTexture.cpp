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
    // 인자로 들어온 경로를 통한 이미지 비트맵 로딩
    m_hBit = (HBITMAP)LoadImage(nullptr, _strFilePath.c_str(), 
        IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

    // 이미지 로드 실패
    if (nullptr == m_hBit)
    {
        return false;
    }

    // main DC와 호환되는 새 DC 생성 후 값 입력
    m_hDC = CreateCompatibleDC(CEngine::GetInst()->GetMainDC());
    DeleteObject(SelectObject(m_hDC, m_hBit));
    GetObject(m_hBit, sizeof(BITMAP), &m_Info);

    return true;
}

