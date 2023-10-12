#include "pch.h"
#include "CLevelMgr.h"

#include "CLevel.h"
#include "CStartLevel.h"
#include "CPlayLevel.h"
#include "CEditorLevel.h"

void CLevelMgr::ChangeLevel(LEVEL_TYPE _Type)
{
	// 만약 현재 레벨 => 현재 레벨로 이동 시
	if (m_pCurLevel == m_arrLevels[(UINT)_Type])
		return;

	// 첫 레벨 생성 여부
	if (nullptr != m_pCurLevel)
		m_pCurLevel->exit();

	m_pCurLevel = m_arrLevels[(UINT)_Type];

	m_pCurLevel->enter();
	m_pCurLevel->begin();
}

void CLevelMgr::init()
{
	// 레벨 생성
	m_arrLevels[(UINT)LEVEL_TYPE::START_LEVEL]	= new CStartLevel;
	m_arrLevels[(UINT)LEVEL_TYPE::PLAY_LEVEL]	= new CPlayLevel;
	m_arrLevels[(UINT)LEVEL_TYPE::EDITOR_LEVEL]	= new CEditorLevel;

	// init
	for (UINT i = 0; i < (UINT)LEVEL_TYPE::END; ++i)
	{
		m_arrLevels[i]->init();
	}

	

	// level
	::ChangeLevel(LEVEL_TYPE::EDITOR_LEVEL);

}

void CLevelMgr::tick()
{
	if (nullptr != m_pCurLevel)
		m_pCurLevel->tick();
}

void CLevelMgr::render(HDC _dc)
{
	m_pCurLevel->render(_dc);

}

CLevelMgr::CLevelMgr()
	:m_pCurLevel(nullptr)
{

}

CLevelMgr::~CLevelMgr()
{
	if (nullptr != m_pCurLevel)
	{
		delete m_pCurLevel;
	}
}