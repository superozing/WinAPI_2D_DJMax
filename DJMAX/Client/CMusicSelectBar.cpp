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
#pragma region _	��Ŀ�� �ؽ����� ���� �� �����ϱ�

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
	// 1. ���� Pos Y ���� ���� ��µ� ��ġ�� �������־�� ��.
	// 2. ��� �� ��ġ�� Ȯ���ǰ� ����, �ٹ� �̹����� ������ ������ش�.
	// 3. �ٹ� �̹����� ������ ũ��� ���� render �� ����,
	// 4. ���� blend ���� ���� ���� ��� ���θ� �����ϱ�.

	// �ϴ� ��ư UI�� UI �Ŵ����� �����ϱ� ������ �̰��� ��� ó������ ���� �����ε�.....
	// UI �Ŵ����� ���� ���캸�ƾ� �Ѵ�.
#pragma region _		AlbumTex render

	if (m_AlbumTexture != nullptr)
	{
		POINT pos = { GetPos().x, GetPos().y };
		POINT ImgScale = { m_AlbumTexture->GetWidth(), m_AlbumTexture->GetHeight() };

		// ���� ���� ���� ����ϵ��� ���� ���ֱ�.
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
