#pragma once
#include "CObj.h"

class CPlayRank :
    public CObj
{
private:
    CTexture* m_RankAtlas;
    int m_PlayRankIdx;
    float diameterRatio;
public:
    virtual void render(HDC _dc) override;

public:
    void SetRank(PLAY_RANK_IDX _idx) {
        m_PlayRankIdx = (int)_idx;
    }

public:
    CLONE_DISABLE(CPlayRank);
    CPlayRank();
    CPlayRank(const CPlayRank& _Origin) = delete;
    ~CPlayRank();
};

