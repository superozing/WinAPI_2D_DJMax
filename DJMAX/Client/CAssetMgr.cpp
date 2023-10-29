#include "pch.h"
#include "CAssetMgr.h"

#include "CPathMgr.h"
#include "CTexture.h"
#include "CSound.h"


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

	// 모든 사운드 해제
	for (const auto& pair : m_mapSound)
	{
		delete pair.second;
	}
}

// 텍스쳐를 파일로부터 불러옴
// 1. map에 저장할(또는 저장된 데이터를 불러올) 키 값 2. 상대 경로(기존 폴더 경로를 제외한 텍스쳐까지의 상대적 경로)
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

// 1. map에 넣을 키 값 2. 폭 3. 높이
CTexture* CAssetMgr::CreateTexture(const wstring& _strKey, UINT _width, UINT _height)
{
	// 입력된 키에 해당하는 텍스쳐가 있는지 확인
	CTexture* pTexture = FindTexture(_strKey);
	if (nullptr != pTexture)
	{
		// 이미 있는 텍스쳐면 찾은걸 반환
		return pTexture;
	}

	// 새 텍스쳐 Create
	pTexture = new CTexture;
	pTexture->Create(_width, _height);

	// Asset 에 키값과 경로값을 알려준다.
	pTexture->m_strKey = _strKey;
	m_mapTex.insert(make_pair(_strKey, pTexture));
	return pTexture;
}

// 찾았을 경우 해당 텍스쳐를, 찾지 못했을 경우 nullptr을 반환함.
// 1. 키 값
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


// 1. 키 값 2. 상대 경로
CSound* CAssetMgr::LoadSound(const wstring& _strKey, const wstring& _strRelativePath)
{
	// 입력된 키에 해당하는 텍스쳐가 있는지 확인한다.
	CSound* pSound = FindSound(_strKey);
	if (nullptr != pSound)
	{
		// 이미 있는 텍스쳐면 찾은걸 반환해준다.
		return pSound;
	}

	// 입력된 키에 해당하는 텍스쳐가 없으면 로딩해서 반환해준다.
	wstring strContentPath = CPathMgr::GetContentPath();
	wstring strFilePath = strContentPath + _strRelativePath;

	pSound = new CSound;

	if (!pSound->Load(strFilePath))
	{
		// 텍스쳐 로드가 실패한 경우(경로 문제 등등..)
		delete pSound;
		return nullptr;
	}

	// Asset 에 키값과 경로값을 알려준다.
	pSound->m_strKey = _strKey;
	pSound->m_strRelativePath = _strRelativePath;

	m_mapSound.insert(make_pair(_strKey, pSound));

	return pSound;
}

// 1. 키 값
CSound* CAssetMgr::FindSound(const wstring& _strKey)
{
	map<wstring, CSound*>::iterator iter = m_mapSound.find(_strKey);

	if (iter == m_mapSound.end())
	{
		return nullptr;
	}

	return iter->second;
}