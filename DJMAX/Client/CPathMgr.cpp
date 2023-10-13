#include "pch.h"
#include "CPathMgr.h"

void CPathMgr::init()
{
	// 실행 파일 경로
	GetCurrentDirectory(255, g_szContent);
	// MessageBox(nullptr, g_szContent, L"Current Directory Check", MB_OK);


	// 상대 경로로 변환
	for (size_t i = wcslen(g_szContent) - 1; i >= 0; --i)
	{
		if ('\\' == g_szContent[i])
		{
			g_szContent[i + 1] = '\0';
			break;
		}
	}
	wcscat_s(g_szContent, 255, L"content\\");
}
