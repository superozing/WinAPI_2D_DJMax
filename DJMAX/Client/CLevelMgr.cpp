#include "pch.h"
#include "CLevelMgr.h"

#include "CEngine.h"

// Level
#include "CLevel.h"
#include "CPlayLevel.h"
#include "CStartLevel.h"
#include "CEditorLevel.h"

// Manager
#include "CLogMgr.h"
#include "CAssetMgr.h"

CLevelMgr::CLevelMgr()
	:m_pCurLevel(nullptr)
	,m_arrLevels{}
{

}

CLevelMgr::~CLevelMgr()
{
	for (UINT i = 0; i < (UINT)LEVEL_TYPE::END; ++i)
	{
		if (nullptr != m_arrLevels[i])
			delete m_arrLevels[i];
	}
}


void CLevelMgr::init()
{
	// 레벨 생성
	m_arrLevels[(UINT)LEVEL_TYPE::START_LEVEL]	= new CStartLevel;
	m_arrLevels[(UINT)LEVEL_TYPE::PLAY_LEVEL]	= new CPlayLevel;
	m_arrLevels[(UINT)LEVEL_TYPE::EDITOR_LEVEL]	= new CEditorLevel;
	/*레벨 추가 시 추가적으로 생성해주어야 함.*/

	// init
	for (UINT i = 0; i < (UINT)LEVEL_TYPE::END; ++i)
	{
		m_arrLevels[i]->init();
	}

	// Asset Load

	// 1. 공통 사용
	CAssetMgr::GetInst()->LoadTexture(L"background_default", L"content\\texture\\outgame\\title_bg.png"); // 배경화면(기본)


	// 2. 레벨의 오브젝트 전용
	CAssetMgr::GetInst()->LoadTexture(L"LevelSelectBtn_Editor_MouseOn", L"texture\\1-cutout.png");
	CAssetMgr::GetInst()->LoadTexture(L"LevelSelectBtn_Select_MouseOn", L"texture\\2-cutout.png");
	CAssetMgr::GetInst()->LoadTexture(L"이미지5", L"texture\\1-cutout.png");
	

	// level 실행
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
	CLogMgr::GetInst()->tick(_dc);

	// BitMap copy
	BitBlt(CEngine::GetInst()->GetMainDC(), 0, 0, ptResolution.x, ptResolution.y, _dc, 0, 0, SRCCOPY);


}

void CLevelMgr::ChangeLevel(LEVEL_TYPE _Type)
{
	// 만약 현재 레벨 => 현재 레벨로 이동 시 레벨을 전환하는 의미가 없음.
	if (m_pCurLevel == m_arrLevels[(UINT)_Type])
		return;

	// 레벨 생성 여부
	if (nullptr != m_pCurLevel)
		m_pCurLevel->exit();

	m_pCurLevel = m_arrLevels[(UINT)_Type];

	m_pCurLevel->enter();

	m_pCurLevel->begin();
}