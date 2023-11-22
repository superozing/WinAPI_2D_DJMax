#pragma once
#include "CObj.h"

class CMusicInfo :
    public CObj
{
private:

	vector<MUSICINFO> m_vecMusicInfo;
	//vector<
	int m_FocusIdx;

private:
	virtual void tick(float _DT) override;
	virtual void render(HDC _dc) override;
	void AlbumTexRender(HDC _dc);
public:
	MUSICINFO* GetMusicInfo() { return &(m_vecMusicInfo[m_FocusIdx]); }
	void AddMusicInfo(CSound* _pMusic, wstring _wstrMusicName, CTexture* _pMusicNameTex, CTexture* _pMainTex, CTexture* _pAlbumTex, int _iBPM, int _iRecord, int _iCombo);

	void SetMusicInfoIdx(int _idx) { m_FocusIdx = _idx; }


public:
	CLONE_DISABLE(CMusicInfo);
	CMusicInfo();
	CMusicInfo(const CMusicInfo& _Origin) = delete;
	~CMusicInfo();

	friend class CMusicAlbumTex;
};

