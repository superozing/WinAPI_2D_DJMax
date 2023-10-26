#pragma once
#include "CEntity.h"

class CAsset :
    public CEntity
{
private:
    // map 안에 저장 되어 있는 키 값
    wstring     m_strKey;

    // 파일 경로
    wstring     m_strRelativePath;


public:
    const wstring& GetKey() { return m_strKey; }
    const wstring& GetRelativePath() { return m_strRelativePath; }

private:
    virtual bool Load(const wstring& _strFilePath) = 0;

public:
    CLONE_DISABLE(CAsset); // 에셋이 복제가 된다는 것은 에셋 매니저의 원칙을 무시하는 것 
    CAsset();
    CAsset(const CAsset& _Origin) = delete;
    ~CAsset();

    friend class CAssetMgr;
};

