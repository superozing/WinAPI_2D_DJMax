#pragma once

#include "CAsset.h"

class CSound
	: public CAsset
{

public:
	virtual bool Load(const wstring& _strFilePath) override;
};

