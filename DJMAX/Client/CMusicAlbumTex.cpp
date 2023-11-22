#include "pch.h"
#include "CMusicAlbumTex.h"

#include "CMusicInfo.h"

CMusicAlbumTex::CMusicAlbumTex(CMusicInfo* _musicInfo)
	: m_musicInfo(_musicInfo)
{
}

CMusicAlbumTex::~CMusicAlbumTex()
{
}

void CMusicAlbumTex::render(HDC _dc)
{
	m_musicInfo->AlbumTexRender(_dc);
}

