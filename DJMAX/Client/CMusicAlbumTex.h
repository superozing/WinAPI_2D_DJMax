#pragma once
#include "CObj.h"

class CMusicInfo;


class CMusicAlbumTex :
    public CObj
{
private:
    CMusicInfo* m_musicInfo;

private:
    virtual void render(HDC _dc);

public:
    CLONE_DISABLE(CMusicAlbumTex);
    CMusicAlbumTex(CMusicInfo* _musicInfo);
    CMusicAlbumTex(const CMusicAlbumTex& _Origin) = delete;
    ~CMusicAlbumTex();
};

