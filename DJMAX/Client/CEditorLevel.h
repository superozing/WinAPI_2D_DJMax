#pragma once
#include "CLevel.h"

class CGear;
class CSound;
class CNote;
class CGear_EditorLevel;

class CEditorLevel :
    public CLevel
{
private:
	CGear_EditorLevel*			m_pGear;
public:
	

	virtual void init() override;
	virtual void enter() override;
	virtual void exit() override;
	virtual void tick() override;

public:
	void OpenNoteEditWindow(CNote* _pEditNote);

};

