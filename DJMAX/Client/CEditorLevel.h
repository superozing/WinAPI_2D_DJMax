#pragma once
#include "CLevel.h"

class CSound;
class CNote;

class CEditorLevel :
    public CLevel
{
private:
	CSound*			m_pMusic;
public:
	

	virtual void init() override;
	virtual void enter() override;
	virtual void exit() override;
	virtual void tick() override;

public:
	void OpenNoteModifyWindow();

};

