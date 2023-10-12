#include "pch.h"
#include "CLevelMgr.h"

#include "CEngine.h"
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
	if (nullptr == m_pCurLevel)
		return;

	// 화면 Clear
	POINT ptResolution = CEngine::GetInst()->GetResolution();
	Rectangle(_dc, -1, -1, ptResolution.x + 1, ptResolution.y + 1);

	// 레벨 render
	m_pCurLevel->render(_dc);

	// Log manager tick(겸사겸사)

	// BitMap copy
	BitBlt(CEngine::GetInst()->GetMainDC(), 0, 0, ptResolution.x, ptResolution.y, _dc, 0, 0, SRCCOPY);


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