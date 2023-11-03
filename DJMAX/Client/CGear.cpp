#include "pch.h"
#include "CGear.h"

#include "CAssetMgr.h"
#include "CTimeMgr.h"
#include "CPathMgr.h"
#include "CKeyMgr.h"

#include "CTexture.h"
#include "CNote.h"
#include "CSound.h"
#include "resource.h"
#include "CLevel.h"

CGear::CGear()
	:m_blendFunc{}
	,m_vecNotes()
	,m_GearTexture(nullptr)
	,m_AccMusicTime(0.f)
{
	// blend function setting
	m_blendFunc.BlendOp = AC_SRC_OVER;
	m_blendFunc.BlendFlags = 0;

	m_blendFunc.SourceConstantAlpha = 255; // 0 ~ 255
	m_blendFunc.AlphaFormat = AC_SRC_ALPHA; // 0
	
	// texture
	m_GearTexture = FINDTEX(L"gear_default");
	SetPos(Vec2(50,-13));

	// 판정선을 가져올 게 아니라, 그냥 기어 프레임과 안 쪽 노트 부분을 구분해야겠는데?
	m_GearJudgeLine = FINDTEX(L"판정선");

}

CGear::~CGear()
{
}

void CGear::tick(float _DT)
{
	Super::tick(_DT);
	m_AccMusicTime += DT;
	//m_curMusicTime = 141 - m_AccMusicTime / ;

	if (KEY_TAP(KEY::A))
	{
		AddNote(NOTE_TYPE::DEFAULT, m_AccMusicTime, m_AccMusicTime, GEARLINE_TYPE::_1);
	}
	if (KEY_TAP(KEY::S))
	{
		AddNote(NOTE_TYPE::DEFAULT, m_AccMusicTime, m_AccMusicTime, GEARLINE_TYPE::_2);
	}
	if (KEY_TAP(KEY::NUM1))
	{
		AddNote(NOTE_TYPE::DEFAULT, m_AccMusicTime, m_AccMusicTime, GEARLINE_TYPE::_3);
	}
	if (KEY_TAP(KEY::NUM2))
	{
		AddNote(NOTE_TYPE::DEFAULT, m_AccMusicTime, m_AccMusicTime, GEARLINE_TYPE::_4);
	}

	if (KEY_TAP(KEY::NUM9))
	{
		SaveNoteData();
	}
	
}

void CGear::render(HDC _dc)
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();
	if (nullptr != m_GearTexture)
	{
		Vec2 vImgScale = Vec2((float)m_GearTexture->GetWidth(), (float)m_GearTexture->GetHeight());
		AlphaBlend(_dc
			, int(vPos.x), int(vPos.y)
			, int(vImgScale.x * 0.8333f), int(vImgScale.y * 0.8333f)
			, m_GearTexture->GetDC()
			, 0, 0
			, int(vImgScale.x), int(vImgScale.y)
			, m_blendFunc);
	}


	for (auto& iter : m_vecNotes)
	{
		iter.render(_dc, m_AccMusicTime, 8.f);
	}

	if (nullptr != m_GearTexture)
	{
		Vec2 vImgScale = Vec2((float)m_GearJudgeLine->GetWidth(), (float)m_GearJudgeLine->GetHeight());
		AlphaBlend(_dc
			, int(vPos.x), int(vPos.y)
			, 418, int(vImgScale.y * 0.8333f)
			, m_GearTexture->GetDC()
			, 0, 0
			, int(vImgScale.x), int(vImgScale.y)
			, m_blendFunc);
	}


	Super::render(_dc);
}

void CGear::AddNote(NOTE_TYPE _type, float _tapTime, float _pressTime, GEARLINE_TYPE _line)
{
	m_vecNotes.push_back(CNote(_type, _tapTime, _pressTime, _line, this));
}

void CGear::LoadNoteData()
{
	// open a file name
	OPENFILENAME ofn = {};

	wstring strTileFolderPath = CPathMgr::GetContentPath();
	strTileFolderPath += L"note\\";

	wchar_t szFilePath[256] = {};

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFilePath;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = 256;
	ofn.lpstrFilter = L"Note\0*.note\0ALL\0*.*";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = strTileFolderPath.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (false == GetOpenFileName(&ofn))
		return;


	FILE* pFile = nullptr;
	_wfopen_s(&pFile, szFilePath, L"rb");

	// 타일 개수
	size_t sizeBuf = 0;
	fread(&sizeBuf, sizeof(size_t), 1, pFile);

	m_vecNotes.reserve(sizeBuf);

	for (size_t i = 0; i < sizeBuf; ++i)
	{
		CNote newdata;
		m_vecNotes.push_back(newdata.Load(pFile, this));
	}

	fclose(pFile);
}

void CGear::SaveNoteData()
{
	// open a file name
	OPENFILENAME ofn = {};

	wstring strTileFolderPath = CPathMgr::GetContentPath();
	strTileFolderPath += L"note\\";


	wchar_t szFilePath[256] = {};

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFilePath;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = 256;
	ofn.lpstrFilter = L"Note\0*.note\0ALL\0*.*";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = strTileFolderPath.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (false == GetSaveFileName(&ofn))
		return;

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, szFilePath, L"wb");


	// 타일 개수
	size_t sizeBuf = m_vecNotes.size();
	fwrite(&sizeBuf, sizeof(size_t), 1, pFile);

	for (auto& iter: m_vecNotes)
	{
		iter.Save(pFile);
	}


	fclose(pFile);
}
