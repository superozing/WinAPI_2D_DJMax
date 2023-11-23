#include "pch.h"
#include "CMusicInfo.h"
#include "CAssetMgr.h"
#include "CStringTexture.h"
#include "CNumTexture.h"
#include "CMusicSelectBar.h"
#include "CFocusUI.h"
#include "CSelectLevel.h"

/// <summary>
/// 음악 정보를 추가함
/// </summary>
/// <param name="_pMusic">_			음악 포인터</param> 
/// <param name="_wstrMusicName">_	음악 이름 L문자열</param>
/// <param name="_pMusicNameTex">_	음악 이름과 작곡가 텍스쳐 포인터</param>
/// <param name="_pMainTex">_		왼 쪽 상단에 곡 정보와 노출될 메인 텍스쳐 포인터</param>
/// <param name="_pAlbumTex">_		포커스 바 와 같이 출력될 1x1비율의 이미지 텍스쳐 포인터</param>
/// <param name="_iBPM">_			음악의 BPM</param>
/// <param name="_iRecord">_		최고 점수</param>
/// <param name="_iCombo">_			최대 콤보</param>
/// <param name="_iDifficult">_		난이도 (양수 - 1~15, 음수 - sc1~sc15)</param>
void CMusicInfo::AddMusicInfo	(	
									CSound*			_pMusic,
									wstring			_wstrMusicName,
								
									CTexture*		_pMusicNameTex,
									CTexture*		_pMainTex,
									CTexture*		_pAlbumTex,
								
									int				_iBPM,
									int				_iRecord,
									int				_iCombo	,
									
									int				_iDifficult
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
	NewMusicData.pBPMTex->SetIntNum(_iBPM);
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

	NewMusicData.iDifficult = _iDifficult;

	m_vecMusicInfo.push_back(NewMusicData);

	CFocusUI* focusUI = new CFocusUI(this);
	focusUI->SetPos(Vec2(575, 200 + (m_vecMusicInfo.size() * 80)));
	m_pOwnerLevel->AddObject(LAYER::UI, focusUI);

	CMusicSelectBar* selectBar = new CMusicSelectBar(m_vecMusicInfo.back(), focusUI, focusUI->GetPos(), m_vecSelectBar.size(), this);
	m_vecSelectBar.push_back(selectBar);

	if (m_vecSelectBar.size()) m_vecSelectBar.operator[](m_FocusIdx)->SetFocus();
}
// X: 575, W: 925 - 60  = 865
// 음... 그러면 이대로 텍스쳐를 만들어보는게 좋아보이죠?



CMusicInfo::CMusicInfo(CSelectLevel* _pOwnerLevel)
	:m_FocusIdx(0)
	, m_pOwnerLevel(_pOwnerLevel)
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

	for (auto& iter : m_vecSelectBar)
	{
		delete iter;
	}
}

void CMusicInfo::tick(float _DT)
{
	CObj::tick(_DT);
	for (auto& iter : m_vecSelectBar)
	{
		iter->tick(_DT);
	}
}

void CMusicInfo::render(HDC _dc)
{
#pragma region _		포커싱 음악 정보 render
	m_vecMusicInfo[m_FocusIdx].pMusicNameTex->render(_dc);
	m_vecMusicInfo[m_FocusIdx].pBPMTex		->render(_dc);
	m_vecMusicInfo[m_FocusIdx].pRecordTex	->render(_dc);
	m_vecMusicInfo[m_FocusIdx].pComboTex	->render(_dc);
#pragma endregion

#pragma region _		순회

	for (int i = 0; i < m_vecSelectBar.size(); ++i)
	{
		m_vecSelectBar.operator[](i)->render(_dc);
	}



#pragma endregion
}

void CMusicInfo::AlbumTexRender(HDC _dc)
{
	m_vecMusicInfo[m_FocusIdx].pMainTex->render(_dc);
}

/////////////////////////////////////////////

void CMusicInfo::SetMusicInfoIdx(int _idx)
{
	m_vecSelectBar.operator[](m_FocusIdx)->SetUnFocus();
	m_FocusIdx = _idx;
	m_vecSelectBar.operator[](m_FocusIdx)->SetFocus();
}