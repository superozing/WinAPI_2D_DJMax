#include "pch.h"
#include "CMusicInfo.h"
#include "CAssetMgr.h"
#include "CStringTexture.h"
#include "CNumTexture.h"
#include "CMusicSelectBar.h"
#include "CFocusUI.h"
#include "CSelectLevel.h"

/// <summary>
/// ���� ������ �߰���
/// </summary>
/// <param name="_pMusic">_			���� ������</param> 
/// <param name="_wstrMusicName">_	���� �̸� L���ڿ�</param>
/// <param name="_pMusicNameTex">_	���� �̸��� �۰ �ؽ��� ������</param>
/// <param name="_pMainTex">_		�� �� ��ܿ� �� ������ ����� ���� �ؽ��� ������</param>
/// <param name="_pAlbumTex">_		��Ŀ�� �� �� ���� ��µ� 1x1������ �̹��� �ؽ��� ������</param>
/// <param name="_iBPM">_			������ BPM</param>
/// <param name="_iRecord">_		�ְ� ����</param>
/// <param name="_iCombo">_			�ִ� �޺�</param>
/// <param name="_iDifficult">_		���̵� (��� - 1~15, ���� - sc1~sc15)</param>
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
// ��... �׷��� �̴�� �ؽ��ĸ� �����°� ���ƺ�����?



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
#pragma region _		��Ŀ�� ���� ���� render
	m_vecMusicInfo[m_FocusIdx].pMusicNameTex->render(_dc);
	m_vecMusicInfo[m_FocusIdx].pBPMTex		->render(_dc);
	m_vecMusicInfo[m_FocusIdx].pRecordTex	->render(_dc);
	m_vecMusicInfo[m_FocusIdx].pComboTex	->render(_dc);
#pragma endregion

#pragma region _		��ȸ

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