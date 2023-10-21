#include "pch.h"
#include "CAssetMgr.h"

#include "CPathMgr.h"
#include "CTexture.h"


CAssetMgr::CAssetMgr()
{

}

CAssetMgr::~CAssetMgr()
{
	// 모든 텍스쳐 해제
	for (const auto& pair : m_mapTex)
	{
		delete pair.second;
	}

	// 모든 사운드 해제 (예정)
	// ... 
}

CTexture* CAssetMgr::LoadTexture(const wstring& _strKey, const wstring& _strRelativePath)
{
	// 입력된 키에 해당하는 텍스쳐가 있는지 확인한다.
	CTexture* pTexture = FindTexture(_strKey);
	if (nullptr != pTexture)
	{
		// 이미 있는 텍스쳐면 찾은걸 반환해준다.
		return pTexture;
	}

	// 입력된 키에 해당하는 텍스쳐가 없으면 로딩해서 반환해준다.
	wstring strContentPath = CPathMgr::GetContentPath();
	wstring strFilePath = strContentPath + _strRelativePath;

	pTexture = new CTexture;

	if (!pTexture->Load(strFilePath))
	{
		// 텍스쳐 로드가 실패한 경우(경로 문제 등등..)
		delete pTexture;
		return nullptr;
	}

	// Asset 에 키값과 경로값을 알려준다.
	pTexture->m_strKey = _strKey;
	pTexture->m_strRelativePath = _strRelativePath;

	m_mapTex.insert(make_pair(_strKey, pTexture));

	return pTexture;
}

CTexture* CAssetMgr::FindTexture(const wstring& _strKey)
{
	// 해당 텍스쳐가 전에 만들어졌는가?
	map<wstring, CTexture*>::iterator iter = m_mapTex.find(_strKey);

	// 노
	if (iter == m_mapTex.end())
	{
		return nullptr;
	}

	// 예스
	return iter->second;
}
