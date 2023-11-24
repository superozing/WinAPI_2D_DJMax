#pragma once
#include "CObj.h"

class CMusicSelectBar;
class CSelectLevel;



class CMusicInfo :
    public CObj
{
private:

	vector<MUSICINFO>			m_vecMusicInfo;
	vector<CMusicSelectBar*>		m_vecSelectBar;
	int							m_FocusIdx;


	CSelectLevel* m_pOwnerLevel;
private:
	virtual void tick(float _DT) override;
	virtual void render(HDC _dc) override;
	void AlbumTexRender(HDC _dc);
public:
	MUSICINFO* GetMusicInfo() { return &(m_vecMusicInfo[m_FocusIdx]); }
	void AddMusicInfo(CSound* _pMusic
		, wstring _wstrMusicName
		, CTexture* _pMusicNameTex = nullptr
		, CTexture* _pMainTex = nullptr
		, CTexture* _pAlbumTex = nullptr
		, int _iBPM = 0
		, int _iRecord = 0
		, int _iCombo = 0
		, int _iDifficult = 0);

	void SetMusicInfoIdx(int _idx);

	vector<CMusicSelectBar*>& GetSelectBar() { return m_vecSelectBar; }

public:
	CLONE_DISABLE(CMusicInfo);
	CMusicInfo(CSelectLevel* _pOwnerLevel);
	CMusicInfo(const CMusicInfo& _Origin) = delete;
	~CMusicInfo();

	friend class CMusicAlbumTex;
};

