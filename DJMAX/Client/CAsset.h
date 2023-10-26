#pragma once
#include "CEntity.h"

class CAsset :
    public CEntity
{
private:
    // map �ȿ� ���� �Ǿ� �ִ� Ű ��
    wstring     m_strKey;

    // ���� ���
    wstring     m_strRelativePath;


public:
    const wstring& GetKey() { return m_strKey; }
    const wstring& GetRelativePath() { return m_strRelativePath; }

private:
    virtual bool Load(const wstring& _strFilePath) = 0;

public:
    CLONE_DISABLE(CAsset); // ������ ������ �ȴٴ� ���� ���� �Ŵ����� ��Ģ�� �����ϴ� �� 
    CAsset();
    CAsset(const CAsset& _Origin) = delete;
    ~CAsset();

    friend class CAssetMgr;
};

