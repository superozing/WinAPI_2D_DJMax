#include "pch.h"
#include "CAssetMgr.h"

#include "CPathMgr.h"
#include "CTexture.h"


CAssetMgr::CAssetMgr()
{

}

CAssetMgr::~CAssetMgr()
{
	// ��� �ؽ��� ����
	for (const auto& pair : m_mapTex)
	{
		delete pair.second;
	}

	// ��� ���� ���� (����)
	// ... 
}

CTexture* CAssetMgr::LoadTexture(const wstring& _strKey, const wstring& _strRelativePath)
{
	// �Էµ� Ű�� �ش��ϴ� �ؽ��İ� �ִ��� Ȯ���Ѵ�.
	CTexture* pTexture = FindTexture(_strKey);
	if (nullptr != pTexture)
	{
		// �̹� �ִ� �ؽ��ĸ� ã���� ��ȯ���ش�.
		return pTexture;
	}

	// �Էµ� Ű�� �ش��ϴ� �ؽ��İ� ������ �ε��ؼ� ��ȯ���ش�.
	wstring strContentPath = CPathMgr::GetContentPath();
	wstring strFilePath = strContentPath + _strRelativePath;

	pTexture = new CTexture;

	if (!pTexture->Load(strFilePath))
	{
		// �ؽ��� �ε尡 ������ ���(��� ���� ���..)
		delete pTexture;
		return nullptr;
	}

	// Asset �� Ű���� ��ΰ��� �˷��ش�.
	pTexture->m_strKey = _strKey;
	pTexture->m_strRelativePath = _strRelativePath;

	m_mapTex.insert(make_pair(_strKey, pTexture));

	return pTexture;
}

CTexture* CAssetMgr::FindTexture(const wstring& _strKey)
{
	// �ش� �ؽ��İ� ���� ��������°�?
	map<wstring, CTexture*>::iterator iter = m_mapTex.find(_strKey);

	// ��
	if (iter == m_mapTex.end())
	{
		return nullptr;
	}

	// ����
	return iter->second;
}
