#include "pch.h"
#include "CMusicSelectBar.h"
#include "CFocusUI.h"
#include "CTexture.h"
#include "CStringTexture.h"


CMusicSelectBar::CMusicSelectBar(MUSICINFO& _MusicInfo, CFocusUI* _FocusUI, Vec2 vPos, int _index, CMusicInfo* _pOwnerMusicInfo)
	:m_FocusUI(_FocusUI)
	,m_AlbumTexture(nullptr)
	,m_isFocus(false)
	,m_MusicInfo(_MusicInfo)
	,blend{AC_SRC_OVER, 0, 0, AC_SRC_ALPHA}
	,index(_index)
	,m_pOwnerInfo(_pOwnerMusicInfo)
	, alpha(0)
{
	SetPos(vPos);
	m_FocusUI->SetOwnerBar(this);
	m_AlbumTexture = m_MusicInfo.pAlbumTex->GetTexture();
}

CMusicSelectBar::~CMusicSelectBar()
{
}

void CMusicSelectBar::tick(float _DT)
{
#pragma region _	포커스 텍스쳐의 알파 값 조절하기

	if (m_isFocus == false && alpha > 0)
	{
		alpha -= 1000.f * _DT;
		if (0.f > alpha) alpha = 0.f;
	}
	else if (m_isFocus == true && alpha < 255)
	{
		alpha += 1000.f * _DT;
		if (255.f < alpha) alpha = 255.f;
	}

	blend.SourceConstantAlpha = (int)alpha;

#pragma endregion
}

void CMusicSelectBar::render(HDC _dc)
{
	// 1. 나의 Pos Y 값에 따라서 출력될 위치를 조정해주어야 함.
	// 2. 출력 될 위치가 확정되고 나면, 앨범 이미지와 라인을 출력해준다.
	// 3. 앨범 이미지를 일정한 크기로 먼저 render 한 다음,
	// 4. 현재 blend 알파 값에 따라서 출력 여부를 결정하기.

	// 일단 버튼 UI는 UI 매니저가 관리하기 때문에 이것을 어떻게 처리해줄 지가 문제인데.....
	// UI 매니저를 조금 살펴보아야 한다.
#pragma region _		AlbumTex render

	if (m_AlbumTexture != nullptr)
	{
		POINT pos = { GetPos().x, GetPos().y };
		POINT ImgScale = { m_AlbumTexture->GetWidth(), m_AlbumTexture->GetHeight() };

		// 알파 원본 값을 출력하도록 세팅 해주기.
		static BLENDFUNCTION blendbuf = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };

		AlphaBlend(_dc
			, pos.x, pos.y
			, 72, 72
			, m_AlbumTexture->GetDC()
			, 0, 0
			, ImgScale.x, ImgScale.y
			, blendbuf);
	}

#pragma endregion

}
