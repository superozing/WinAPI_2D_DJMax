#include "pch.h"
#include "CPathMgr.h"

void CPathMgr::init()
{
	// ���� ���� ���
	GetCurrentDirectory(255, g_szContent);
	// MessageBox(nullptr, g_szContent, L"Current Directory Check", MB_OK);


	// ��� ��η� ��ȯ
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