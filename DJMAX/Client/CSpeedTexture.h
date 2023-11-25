#pragma once
#include "CObj.h"

class CSpeedTexture :
    public CObj
{
private:
	CTexture*		m_SpeedIconBgAtlas;
	CTexture*		m_SpeedIcon_00Atlas;

	int				m_iSpeed;

	BLENDFUNCTION	m_blendFunc;


private:
	virtual void tick(float _DT) override;
	virtual void render(HDC _dc) override;

public:
	int GetSpeed() { return m_iSpeed; }
	void SetSpeed(int _speed) { m_iSpeed = _speed; }

public:
	CLONE_DISABLE(CSpeedTexture);
	CSpeedTexture();
	CSpeedTexture(const CSpeedTexture& _Origin) = delete;
	~CSpeedTexture();

};