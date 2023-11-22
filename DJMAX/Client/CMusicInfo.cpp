#include "pch.h"
#include "CMusicInfo.h"
#include "CAssetMgr.h"
#include "CStringTexture.h"
#include "CNumTexture.h"




void CMusicInfo::AddMusicInfo	(	
									CSound*			_pMusic,
									wstring			_wstrMusicName,
								
									CTexture*		_pMusicNameTex,
									CTexture*		_pMainTex,
									CTexture*		_pAlbumTex,
								
									int				_iBPM,
									int				_iRecord,
									int				_iCombo		
								)

{
	MUSICINFO NewMusicData;

	NewMusicData.pMusic = _pMusic;

	NewMusicData.wstrMusicName = _wstrMusicName;

	NewMusicData.pMusicNameTex = new CStringTexture;
	NewMusicData.pMusicNameTex->SetPos(Vec2(80, 200));
	NewMusicData.pMusicNameTex->SetScale(Vec2(500, 100));
	NewMusicData.pMusicNameTex->SetTexture(_pMusicNameTex);

	NewMusicData.pMainTex = new CStringTexture;
	NewMusicData.pMainTex->SetPos(Vec2(67, 183));
	NewMusicData.pMainTex->SetScale(Vec2(430, 370));
	NewMusicData.pMainTex->SetTexture(_pMainTex);

	NewMusicData.pAlbumTex = new CStringTexture;
	NewMusicData.pAlbumTex->SetTexture(_pAlbumTex);


	NewMusicData.iBPM = _iBPM;

	NewMusicData.pBPMTex = new CNumTexture;
	NewMusicData.pBPMTex->SetIntNum(105);
	NewMusicData.pBPMTex->SetPos(Vec2(120, 278));
	NewMusicData.pBPMTex->SetFontSize(20);
	NewMusicData.pBPMTex->SetTexture(FINDTEX(L"num_atlas_lineless"));

	NewMusicData.iRecord = _iRecord;

	NewMusicData.pRecordTex = new CNumTexture;
	NewMusicData.pRecordTex->SetIntNum(_iRecord);
	NewMusicData.pRecordTex->SetFontSize(20);
	NewMusicData.pRecordTex->SetPos(Vec2(190, 450));
	NewMusicData.pRecordTex->SetTexture(FINDTEX(L"num_atlas_lineless"));

	NewMusicData.iCombo = _iCombo;

	NewMusicData.pComboTex = new CNumTexture;
	NewMusicData.pComboTex->SetIntNum(_iCombo);
	NewMusicData.pComboTex->SetFontSize(20);
	NewMusicData.pComboTex->SetPos(Vec2(190, 510));
	NewMusicData.pComboTex->SetTexture(FINDTEX(L"num_atlas_lineless"));

	m_vecMusicInfo.push_back(NewMusicData);
}

CMusicInfo::CMusicInfo()
	:m_FocusIdx(0)
{

}

CMusicInfo::~CMusicInfo()
{
	for (auto& iter : m_vecMusicInfo)
	{
		delete iter.pMusicNameTex;
		delete iter.pMainTex;
		delete iter.pAlbumTex;
		delete iter.pBPMTex;
		delete iter.pRecordTex;
		delete iter.pComboTex;
	}
}

void CMusicInfo::tick(float _DT)
{
}

void CMusicInfo::render(HDC _dc)
{
	m_vecMusicInfo[m_FocusIdx].pMusicNameTex	->render(_dc);

	m_vecMusicInfo[m_FocusIdx].pBPMTex			->render(_dc);
	m_vecMusicInfo[m_FocusIdx].pRecordTex		->render(_dc);
	m_vecMusicInfo[m_FocusIdx].pComboTex		->render(_dc);
}

void CMusicInfo::AlbumTexRender(HDC _dc)
{
	m_vecMusicInfo[m_FocusIdx].pMainTex->render(_dc);
}

