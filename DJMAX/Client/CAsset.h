#pragma once
#include "CEntity.h"

class CAsset :
    public CEntity
{
private:
    // mao 안에 저장 되어 있는 키 값
    wstring     m_strKey;

    // 파일 경로
    wstring     m_strRelativePath;


public:
    const wstring& GetKey() { return m_strKey; }
    const wstring& GetRelativePath() { return m_strRelativePath; }

private:
    virtual bool Load(const wstring& _strFilePath) = 0;

public:
    CAsset();
    ~CAsset();

    friend class CAssetMgr;
};

